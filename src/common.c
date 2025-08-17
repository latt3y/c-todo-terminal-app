#include "../headers/common.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void pwd(char *buff, size_t size)
{
  if (!getcwd(buff, size)) {
    fprintf(stderr, "could not get path to current dir\n");
    exit(EXIT_FAILURE);
  }
}

uint32_t str_len(const char *s)
{
  const char *sr = s;

  while (*sr++);

  return sr - s;
}

void str_join(const char *s1, const char *s2, char *with_str, char *const dest, uint64_t destlen)
{
  uint32_t s1len = str_len(s1);
  uint32_t s2len = str_len(s2);

  if (s1len == 0 && s2len == 0) return;

  if ((s1len + s2len) > destlen)
  {
    fprintf(stderr, "destination length is smaller than the strings you are trying to join\n");
    return;
  }

  char* destp = dest;
  const char* sp = s1;

  while (*sp)
    *destp++ = *sp++;

  if (with_str) {
    while (*with_str)
      *destp++ = *with_str++;
  }

  sp = s2;

  while (*sp)
    *destp++ = *sp++;

  *destp = '\0';
}

void read_line(char *des, uint8_t len)
{
  char *curr = des;

  int ch = getchar();

  // skip spaces and new line
  while (ch == ' ' || ch == '\n')
    ch = getchar();

  uint8_t i = 0;
  uint8_t max = len - 1;

  while (TRUE)
  {
    if (i++ == max)
      break;

    // add more characters that would terminate the program
    if (ch == '\n' || ch == '\x03')
      break;

    *curr++ = ch;

    ch = getchar();
  }

  *curr = '\0';
}

void str_cpy(char *des, const char *str, uint8_t size)
{
  int counter = 0;

  while ((counter++ < size) && *str)
  {
    *des++ = *str++;
  }

  *des = '\0';
}

void list_commands(void) {
  printf("In order to interact with the app you can press: \n\n");
  printf("i - (insert) -  for inserting new todo; \n");
  printf("u - (update) -  for updating an existing todo; \n");
  printf("l - (list)   -  for listing all todos; \n");
  printf("d - (delete) -  for deleting a todo. \n");
  printf("c - (clear)  -  for clearing all todos. \n");
  printf("q - (quit)   -  for quiting the app. \n");
}
