#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../headers/db.h"
#include "../headers/task.h"
#include "../headers/common.h"

#define local static
#define bool uint8_t

extern char abs_path[ABS_PATH_SIZE],
         db_main_path[PATHSIZE],
         db_meta_path[PATHSIZE];

local DB database;
local FILE* data_file;
local FILE* meta_file;
local bool db_is_initialized = FALSE;

FILE* m_fopen(const char* filename, const char* mode)
{
  FILE* file = fopen(filename, mode);

  if (!file)
  {
    fprintf(stderr, "Could not open file %s\n", filename);
    exit(1);
  }

  return file;
}

void m_fread(
    void* buffer,
    size_t size,
    size_t memb,
    FILE *restrict file,
    const char *const filename
)
{
  int ret = fread(buffer, size, memb, file);
  if (ret != memb)
  {
    fprintf(stderr, "Could not read from file %s\n Expected %lu but received %d\n", filename, memb, ret);
    exit(1);
  }
}

void m_fwrite(
    void* buff,
    size_t size,
    size_t memb,
    FILE *restrict file,
    const char *const filename
)
{
  int ret = fwrite(buff, size, memb, file);
  if (ret != memb)
  {
    fprintf(stderr, "Could not write to file %s\n Expected mem output %lu but got %d\n", filename, memb, ret);
    exit(1);
  }
}

void db_init()
{
  if (db_is_initialized) return;

  database.tasks = NULL;
  database.size = 0;
  database.curr_index = 1;

  data_file = m_fopen(db_main_path, "a+b");
  meta_file = m_fopen(db_meta_path, "a+b");

  m_fread(&database.size, sizeof(uint64_t), 1, data_file, DB_MAIN_FILE_NAME);
  m_fread(&database.curr_index, sizeof(uint64_t), 1, meta_file, DB_META_FILE_NAME);
  m_fread(&database.tasks, sizeof(Task), database.size, data_file, DB_MAIN_FILE_NAME);

  db_is_initialized = TRUE;
}

void db_clear_data(void)
{
  if (!db_is_initialized) return;

  fclose(m_fopen(db_main_path, "w"));
  fclose(m_fopen(db_meta_path, "w"));
}

void db_kill(void)
{
  if (data_file) {
    fclose(data_file);
    data_file = NULL;
  }

  if (meta_file) {
    fclose(meta_file);
    meta_file = NULL;
  }
}

void db_store_data_()
{
  if (!data_file)
  {
    fprintf(stderr, "Could not save because \"data file\" is not opened");
    return;
  }

  m_fwrite(
    database.tasks,
    sizeof(Task),
    database.size,
    data_file,
    DB_MAIN_FILE_NAME
  );
}

void db_save_index_()
{
  if (!meta_file)
  {
    fprintf(stderr, "Could not save because \"meta file\" is not opened");
    return;
  }

  m_fwrite(
    &database.curr_index,
    sizeof(uint64_t),
    1,
    meta_file,
    DB_META_FILE_NAME
  );
}
