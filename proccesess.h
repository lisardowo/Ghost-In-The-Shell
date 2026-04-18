
#include "utils.h"
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stddef.h>

#define maxJobs 100

typedef struct 
{
    int id;
    pid_t pid;
    char command[1024];
    bool running;
} job;

extern job jobList[maxJobs];

int addJob(pid_t pid, char *command);
void removeJob(pid_t pid);
void checkBacktroundJobs();
void ignoreSignalsInParent();
void restoreSignalsInChild();