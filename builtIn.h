#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

int type(char *current[][100], bool redirectedstdout ,bool redirectedstderr, bool appendStdErr, bool appendStdOut, char *stdoutPath, char *stderrPath , char *stderrAppendPath , char *stdoutAppendPath);