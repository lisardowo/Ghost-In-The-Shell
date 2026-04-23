
#pragma once

#include "sys/types.h"

typedef struct 
{
    int id;
    pid_t pid;
    char command[1024];
    bool running;
} job;

typedef struct 
{
 
 bool redirectStdout;
 bool  redirectStderr;
 bool  appendStdout;
 bool appendStderr;
 char *stdOutPath;
 char *stdErrPath;
 char *stdoutAppendPath;
 char *stderrAppendPath;

} redirectConfig;

