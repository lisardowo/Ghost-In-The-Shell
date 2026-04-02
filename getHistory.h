
#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void addHistory(char *command, int *historyCount, char *historyBuffer[]);
void dumpHistory(int historyCount, char *historyBuffer[]);
void getHistory(int *historyCount, char *historyBuffer[]);