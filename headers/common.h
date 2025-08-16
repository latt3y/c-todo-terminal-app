#include <stdint.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ABS_PATH_SIZE 512
#define PATHSIZE 1024

void list_commands(void);
void read_line(char *des, uint8_t len);
void str_cpy(char *des, const char *str, uint8_t size);
void pwd(char *buff, size_t size);
uint32_t str_len(const char *);
void str_join(char* dest, uint64_t destlen, char *join_with, const char* s1, const char* s2);
