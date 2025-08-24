#ifndef DB_H
#define DB_H

#include <stdint.h>
#include "./task.h"

#define DB_MAIN_FILE_NAME "/database/main.db"
#define DB_META_FILE_NAME "/database/meta.db"

struct _db {
  uint64_t size = 0;
  void *next;
};

typedef struct _db DB;
typedef struct _db *DBPTR;

void db_init(void);
void db_clear_data(void);
void db_store_data(Task* tasks_buffer, unsigned int *mem_amount);
void db_save_index(uint64_t index);

#endif
