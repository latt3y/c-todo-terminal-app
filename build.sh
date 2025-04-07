#!/bin/bash

date
echo "Building Todo App"

gcc -O1 -std=c99 -Wall -Werror main.c ./lib/task.c ./lib/common.c ./lib/db.c -o main

echo "Builded successfuly"
