#!/bin/bash

date
echo "Building Note App"

gcc -O1 -std=c99 -Wall -Werror main.c ./src/task.c ./src/common.c ./src/db.c -o main

echo "Builded successfuly"
