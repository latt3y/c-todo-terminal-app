#define DB_NAME "./database/main.db"
#define META_FILE_NAME "./database/indexes.db"

void clear_file(void);
void store_into_file(Task *tasks_buffer, unsigned int *mem_amount);
void save_index(unsigned long *index);
