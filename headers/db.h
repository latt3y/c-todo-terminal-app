#include <stdint.h>

#define DB_MAIN_FILE_NAME "./database/main.db"
#define DB_META_FILE_NAME "./database/meta.db"

void clear_file(void);
void store_into_file(Task* tasks_buffer, unsigned int *mem_amount);
void save_index(uint64_t* index);
