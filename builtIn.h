#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include "utils.h"

int type(char **current, bool redirectedstdout ,bool redirectedstderr, bool appendStdErr, bool appendStdOut, char *stdoutPath, char *stderrPath , char *stderrAppendPath , char *stdoutAppendPath);