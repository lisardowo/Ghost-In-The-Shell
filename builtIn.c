
#include "builtIn.h"

int type(char **current, bool redirectedstdout, bool redirectedstderr, bool appendStdOut, bool appendStdErr, char *stdoutPath, char *stderrPath, char *stdoutAppendPath, char *stderrAppendPath)
{
    
    if (current[1] == NULL)
    {
        printf("Usage : type <command>\n") ;
        return 1;
    }
    else if(!strcmp("echo", current[1]) || !strcmp("exit", current[1]) ||
             !strcmp("type", current[1]) || !strcmp("pwd", current[1]) ||
             !strcmp("cd", current[1]) || !strcmp("history", current[1]))
    {

         if(redirectedstdout)
        {
            int fd = getFileDescriptor(stdoutPath, O_TRUNC | O_CREAT | O_WRONLY);
            dprintf(fd,"%s is a shell builtin\n", current[1]);
            return 0;
        }

        if(appendStdOut)
        {
            int fd = getFileDescriptor(stdoutAppendPath, O_APPEND | O_CREAT | O_WRONLY);
            dprintf(fd, "%s is a shell builtin\n", current[1]);
            return 0;
        }

        printf("%s is a shell builtin\n", current[1]);
        return 0;
    }
    else
    {
        if(redirectedstdout)
        {
            int fd = getFileDescriptor(stdoutPath, O_TRUNC | O_CREAT | O_WRONLY);
            char *path = getPath(current[1]);
            if (path != NULL)
            {
                dprintf(fd, "%s is %s\n", current[1], path);
                return  0;
            }
            else
            {
                printf("%s: not found\n", current[1]);
                return 1;
            }
        }


        if(redirectedstderr)
        {
            int fd = getFileDescriptor(stderrPath, O_TRUNC | O_CREAT | O_WRONLY);
            char *path = getPath(current[1]);
            if (path != NULL)
            {
                printf("%s is %s\n", current[1], path);
                return  0;
            }
            else
            {
                dprintf(fd, "%s: not found\n", current[1]);
                return 1;
            }
        }


        if(appendStdOut)
        {
            int fd = getFileDescriptor(stdoutAppendPath, O_APPEND | O_CREAT | O_WRONLY);
            char *path = getPath(current[1]);
            if (path != NULL)
            {
                dprintf(fd, "%s is %s\n", current[1], path);
                return  0;
            }
            else
            {
                printf("%s: not found\n", current[1]);
                return 1;
            }
        }


        if(appendStdErr)
        {
            int fd = getFileDescriptor(stderrAppendPath, O_APPEND | O_CREAT | O_WRONLY);
            char *path = getPath(current[1]);
            if (path != NULL)
            {
                printf("%s is %s\n", current[1], path);
                return  0;
            }
            else
            {
                dprintf(fd, "%s: not found\n", current[1]);
                return 1;
            }
        }

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

    return 1; 
}

int history(char *historyBuffer[])
{
    
    for(int i = 0 ; historyBuffer[i] != NULL ; i++)
      {
        printf("%d %s\n", i + 1, historyBuffer[i]);
      }
    return 0;
}

int pwd()
{
    char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)))
      {
        printf("%s\n",cwd);
        return 0;
      }
      else
      {
        return 1;
      }
}

int cd(char **current)
{
     if (current[1] == NULL || strcmp ("~", current[1]) == 0 )
      {
        char *homePath = getenv("HOME");
        return (chdir(homePath) ) ? 0 : 1;
      }
      else
      {
        if (chdir(current[1]) != 0)
        {
          printf("%s: no such file or directory : \"%s\" \n", current[0], current[1]);
          return 1;
        }
        else
        {
          return 0;
        }
      }
}

int echo(char **current)
{
    
     for (int i = 1 ; current[i] != NULL ; i++)
      {
        printf("%s ", current[i]);
      }
      printf("\n");
      return 0;
}