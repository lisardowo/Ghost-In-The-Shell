#include "binariesManager.h"


char binPath[100000];

char* getPath(char *command)
{
  char *path = getenv("PATH");
  char modifiablePath[10000];
  strncpy(modifiablePath, path, sizeof(modifiablePath));
  modifiablePath[sizeof(modifiablePath) - 1] = '\0';
  char *myPtr = strtok(modifiablePath, ":");

  while(myPtr != NULL) 
  {
    
    snprintf(binPath, sizeof(binPath), "%s/%s", myPtr, command);
    
    if (access(binPath, X_OK) == 0)
    {

      return binPath;

    }
   
    myPtr = strtok(NULL, ":");
  }
  return NULL;
}

void executeBin(char *stdoutPath,char *stdErrPath, bool redirectedstdout, bool redirectedStdErr, bool appendStdOut, bool appendStdErr, char *argv[])
{

  char* binPath = getPath(argv[0]);

  if(binPath == NULL)
  {
    printf("%s: command not found\n", argv[0]);
  }

  if (fork() == 0)
  {
    if(redirectedstdout)
    {
      
      int fdOut = creat(stdoutPath, 0644);
      if (fdOut < 0)
      {
        _exit(1);
      }
      dup2(fdOut, STDOUT_FILENO);
      close(fdOut);

    }
      
    if (redirectedStdErr)
    {
      
      int fdError = creat(stdErrPath, 0644);
      if (fdError < 0)
      {
        _exit(1);
      }
      dup2(fdError, STDERR_FILENO);
      close(fdError);
    }

    if(appendStdOut)
    {
      int fdOut = open(stdoutPath, O_APPEND | O_CREAT | O_WRONLY, 0644);
      if (fdOut < 0)
      {
        _exit(1);
      }
      dup2(fdOut, STDOUT_FILENO);
      close(fdOut);

    }

    if(appendStdErr)
    {
      int fdOut = open(stdErrPath, O_APPEND | O_CREAT | O_WRONLY, 0644);
      if (fdOut < 0)
      {
        _exit(1);
      }
      dup2(fdOut, STDERR_FILENO);
      close(fdOut);

    }

  
    execv(binPath, argv);
    _exit(127);
  }
  else
  {
    wait(NULL);
  }
}
