#ifndef COMMON_H
#define COMMON_H

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
void str_join(const char *s1, const char *s2, char *with_str, char *const dest, uint64_t destlen);

#endif
