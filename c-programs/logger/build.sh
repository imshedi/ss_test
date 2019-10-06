#!/bin/bash

## To enable colouring compile using -DLOG_USE_COLOR

gcc -Wall -Wextra logger.c logtest.c -o logtest

mv logtest.exe logtest
./logtest
