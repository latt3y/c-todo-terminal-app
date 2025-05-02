#include "../headers/common.h"
#include <stdio.h>
#include <stdint.h>

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

  while (counter++ < size && *str)
  {
    *des++ = *str++;
  }

  *des = 0;
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
