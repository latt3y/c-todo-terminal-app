#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../headers/task.h"
#include "../headers/common.h"
#include "../headers/db.h"

#define MAX_TITLE_SIZE 50

uint32_t mem_amount = 0;
uint64_t current_index = 1;
Task *tasks_buffer = NULL;

void help_info(void) {
  printf("> Press \"h\" if you need help for interacting with the app\n");
}

void intro(void) {
  printf("\n================== Tasks ========================\n");
  printf(" $$$ Let's get some job done today! $$$ \n\n");
  help_info();
  printf("\n=================================================\n\n");
}

uint8_t is_valid_op(char *op) {
  printf(">$tasks: ");
  scanf(" %c", op);

  switch (*op) 
  {
    case 'i': 
    case 'u': 
    case 'd': 
    case 'l': 
    case 'q': 
    case 'h':
    case 'c': {
      return TRUE;
    };
    default: return FALSE;
  }
}

void Task_Loop(void)
{
  char op = '\0';

  while (TRUE) 
  {
    if (!is_valid_op(&op)) 
    {
      printf("invalid command! \n\n");
      help_info();
    }
    else if (op == 'q')
    {
      free_tasks_buffer();
      break;
    }
    else
      handle_op(&op);
  }
}

void init_tasks(void)
{
  if (tasks_buffer)
    return;

  FILE *file = fopen(DB_NAME, "rb");
  FILE *meta_file = fopen(META_FILE_NAME, "rb");

  if (!file || !meta_file) {
    printf("Could not load db\n");
    exit(EXIT_FAILURE);
  }

  fread(&mem_amount, sizeof(int), 1, file);

  tasks_buffer = (Task *) malloc((mem_amount + 1) * sizeof(Task));

  if (!tasks_buffer) {
    printf("Could not initialize tasks\n");
    exit(EXIT_FAILURE);
  }

  if (fread(tasks_buffer, sizeof(Task), mem_amount, file) != mem_amount) {
    printf("Something went wrong when reading tasks\n");
    exit(EXIT_FAILURE);
  }

  // load index where it left off
  fread(&current_index, sizeof(int), 1, meta_file);
}

void create_task(void)
{
  Task *task = (Task *) malloc(sizeof(Task));

  task->id = current_index;

  current_index++;

  printf("Enter title (max: %d char): ", MAX_TITLE_SIZE);
  read_line(task->title, MAX_TITLE_SIZE);

  task->status = 0;

  // append new task to the end of the tasks_buffer
  // can use push maybe here
  tasks_buffer[mem_amount++] = *task;

  store_into_file(tasks_buffer, &mem_amount);
  save_index(&current_index);

  free(task);
  task = NULL;
}

void update_task(void)
{
  int option;

  char *title = (char *) malloc(MAX_TITLE_SIZE);

  printf("Task title to update: ");
  read_line(title, MAX_TITLE_SIZE);

  Task *task = NULL;
  
  for (uint32_t i = 0; i < mem_amount; i++) 
  {
    if (strcmp(title, tasks_buffer[i].title) == 0) 
    {
       task = &tasks_buffer[i];
       break;
    }
  }

  if (!task)
  {
    printf("Could not find task! Try again. \n");
    return;
  }

  char *new_title = (char *) malloc(MAX_TITLE_SIZE);

  insert_option: 
    printf("Please press 1 to update name or 2 to update the status: ");
    scanf(" %d", &option);

  switch (option) {
    case 1: {
      goto update_title;
    } break;

    case 2: {
      goto update_status;
    } break;

    default: {
      printf("Invalid option\n");
      goto insert_option;
    };
  }

  update_title:
    printf("Enter tasks new title: ");
    read_line(new_title, MAX_TITLE_SIZE);

    str_cpy(task->title, new_title, MAX_TITLE_SIZE);
    goto end;

  update_status:
    printf("Enter status (1 - done; 0 - undone): ");
    scanf(" %d", (int *) &task->status);

  end: 
    store_into_file(tasks_buffer, &mem_amount);
    free(title);
    free(new_title);
}

void delete_task(void)
{
  char *title;
  int i;

  title = (char *) malloc(50);

  printf("Please enter title of the task to be deleted: ");
  read_line(title, MAX_TITLE_SIZE);

  Task *task = NULL;

  for (i = 0; i < mem_amount; i++) 
  {
    if (strcmp(title, tasks_buffer[i].title) == 0) 
    {
       task = &tasks_buffer[i];
       break;
    }
  }

  if (!task)
  {
    printf("Could not find task! Try again. \n");
    return;
  }

  Task *new_tasks = (Task *) malloc(--mem_amount * sizeof(Task));

  i = 0;

  while (i < mem_amount)
  {
    if (tasks_buffer[i].id != task->id)
      new_tasks[i] = tasks_buffer[i];
    
    i++;
  }

  store_into_file(new_tasks, &mem_amount);
  free(new_tasks);
  free(title);
}

void list_tasks(void)
{
  for (int i = 0; i < mem_amount; i++) {
    Task task = tasks_buffer[i];

    printf(
      "==========\n%d|%s%s%s| status: %s\n",
      i + 1,
      "  ",
      task.title,
      "  ",
      task.status ? "Done" : "Undone"
    );
  }
}

void handle_op(char *op)
{
  if (!tasks_buffer)
  {
    init_tasks();
  }

  switch (*op)
  {
    case 'h': {
      list_commands();  
      break;
    }
    case 'i': {
      create_task();
      break;
    }
    case 'c': {
      if (!mem_amount) 
      {
        return;
      }

      clear_all();
      break;
    }
    case 'd': {
      if (!mem_amount)
      {
        printf("There's nothing to delete\n");
        return;
      }

      delete_task();

      break;
    };
    case 'u': {
      if (!mem_amount)
      {
        printf("There's nothing to update\n");
        return;
      }

      update_task();
      break;
    };
    case 'l': {
      if (!mem_amount)
      {
        printf("Tasks list is empty. Add some tasks! \n");
        return;
      }

      list_tasks();
      break;
    };
  }
}

// reset
void clear_all() 
{
  clear_file();

  mem_amount = 0;
  current_index = 1;
  free_tasks_buffer();
}

void free_tasks_buffer(void)
{
  if (tasks_buffer)
  {
    free(tasks_buffer);
    tasks_buffer = NULL;
  }
}
