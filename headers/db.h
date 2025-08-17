#include <stdint.h>

#define DB_MAIN_FILE_NAME "/database/main.db"
#define DB_META_FILE_NAME "/database/meta.db"

void db_clear_data(void);
void db_store_data(Task* tasks_buffer, unsigned int *mem_amount);
void db_save_index(uint64_t index);
