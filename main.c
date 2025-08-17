#include "./headers/task.h"
#include "./headers/common.h"
#include "./headers/db.h"

char db_main_path[PATHSIZE]  = {0},
     db_meta_path[PATHSIZE]  = {0},
     abs_path[ABS_PATH_SIZE] = {0};

int main(void)
{
  pwd(abs_path, ABS_PATH_SIZE);

  str_join(abs_path, DB_MAIN_FILE_NAME, NULL, db_main_path, PATHSIZE);
  str_join(abs_path, DB_META_FILE_NAME, NULL, db_meta_path, PATHSIZE);

  intro();
  Task_Loop();
  return 0;
}
