#include "./headers/task.h"
#include "./headers/common.h"
#include <stdio.h>

unsigned char is_valid_op(char *op) {
  printf("todos: ");
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

void print_help() {
  printf("Press \"h\" if you need help for\ninteracting with the app\n");
}

void intro(void) {
  printf("\n========== TODOS ==========\n\n");
  print_help();
  printf("\n==============================\n\n");
}

void TaskLoop(void)
{
  char op = '\0';

  while (TRUE) 
  {
    if (!is_valid_op(&op)) 
    {
      printf("the command you entered is invalid! \n\n");
      print_help();
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

int main(void)
{
  intro();
  init_tasks();

  TaskLoop();

  return(0);
}
