#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include "utils.h"

int type(char **current, bool redirectedstdout ,bool redirectedstderr, bool appendStdOut, bool appendStdErr, char *stdoutPath, char *stderrPath , char *stdoutAppendPath, char *stderrAppendPath );
int history(char *historyBuffer[]);
int echo(char **current);
int cd(char **current);
int pwd();