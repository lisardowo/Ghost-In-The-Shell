
#include "builtIn.h"

int type(char *current[][100], bool redirectedstdout ,bool redirectedstderr, bool appendStdErr, bool appendStdOut, char *stdoutPath, char *stderrPath , char *stderrAppendPath , char *stdoutAppendPath)
{
    //int fileDescriptor = getFileDescriptor(stdoutPath , O_TRUNC | O_CREAT | O_WRONLY);
    if (current[1] == NULL)
    {
        printf("Usage : type <command>\n") ;
        return 1;
    }
    else if((!strcmp("echo", current[1]) || !strcmp("exit", current[1]) ||
             !strcmp("type", current[1]) || !strcmp("pwd", current[1]) ||
             !strcmp("cd", current[1]) || !strcmp("history", current[1])) && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
    {
        printf("%s is a shell builtin\n", current[1]);
        return 0;
    }
    else
    {
        char *path = getPath(current[1]);
        if (path != NULL)
        {
          printf("%s is %s\n", current[1], path);
          return  0;
        }
        else
        {
          printf("%s: not found\n", current[1]);
          return 1;
        }
    }
}
