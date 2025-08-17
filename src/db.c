#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../headers/task.h"
#include "../headers/db.h"
#include "../headers/common.h"

extern char abs_path[ABS_PATH_SIZE],
       db_main_path[PATHSIZE],
       db_meta_path[PATHSIZE];

void db_clear_data(void)
{
  fclose(fopen(db_main_path, "w"));
  fclose(fopen(db_meta_path, "w"));
}

void db_store_data(Task *tasks_buffer, unsigned int *mem_amount)
{
  FILE *file;

  file = fopen(db_main_path, "wb");

  if (file == NULL)
  {
    printf("Could not open main file \"%s\"\n", db_main_path);
    exit(EXIT_FAILURE);
  }

  if (fwrite(mem_amount, sizeof(int), 1, file) != 1)
  {
    printf("Could not save to main file %s\n", DB_MAIN_FILE_NAME);
    exit(EXIT_FAILURE);
  }

  if (fwrite(tasks_buffer, sizeof(Task), *mem_amount, file) != *mem_amount) 
  {
    printf("Could not save to file \"%s\"\n", db_main_path);
    exit(EXIT_FAILURE);
  }

  printf("Tasks saved successfuly\n");

  fclose(file);
}

void db_save_index(uint64_t index)
{
  FILE *file;

  file = fopen(db_meta_path, "wb");

  if (file == NULL)
  {
    printf("Could not open file \"%s\"\n", db_meta_path);
    exit(EXIT_FAILURE);
  }

  if (fwrite(&index, sizeof(long), 1, file) != 1) 
  {
    printf("Could not save to file \"%s\"\n", db_meta_path);
    exit(EXIT_FAILURE);
  }

  fclose(file);
}
