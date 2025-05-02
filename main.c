#include "./headers/task.h"
#include "./headers/common.h"

int main(void)
{
  intro();
  init_tasks();

  Task_Loop();

  return(0);
}
