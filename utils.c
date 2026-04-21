
#include <fcntl.h>
#include "utils.h"

char binPath[100000]; 
extern char prompt[1024];
#define generalPermissions 0644

void createPrompt()
{

  char cwd[4096];

  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    snprintf(prompt,sizeof(prompt), "$ ");
    return;
  }


  char modfiable[4096];
  strncpy(modfiable, cwd , sizeof(modfiable) - 1);
  modfiable[sizeof(modfiable) - 1] = 0;

  char *parts[512];
  int count = 0;

  char *token = strtok(modfiable, "/");
  while (token != NULL && count < 511)
  {
    parts[count++] = token;
    token = strtok(NULL, "/");
  }

  if (count >= 2)
  {
    snprintf(prompt, sizeof(prompt), "%s/%s $ ", parts[count - 2] , parts[count - 1]);
  }
  else if (count == 1)
  {
    snprintf(prompt, sizeof(prompt), "%s $ ", parts[0]);
  }
  else
  {
    snprintf(prompt, sizeof(prompt), "$ ");
  }

}

bool isOperator(char *token)
{
    if (token == NULL)
    {
        return false;
    }

    return strcmp(token, ">") == 0 || strcmp(token, "1>") == 0 || strcmp(token, "2>") == 0 || strcmp(token, ">>") == 0 || strcmp(token, "2>>") == 0 || strcmp(token, "&&") == 0 ;
    

}

int getFileDescriptor(const char *descriptorTarget, int flags)
{
  int fileDescriptor = open(descriptorTarget, flags, generalPermissions);
  return fileDescriptor;
}


char* getPath(char *command)
{
  char *path = getenv("PATH");
  
  if (path == NULL)
  {
    return NULL;
  }

  char modifiablePath[4096];
  if (strlen(path) >= sizeof(modifiablePath))
  {
    printf("shell: warning: PATH too long");
  }
  strncpy(modifiablePath, path, sizeof(modifiablePath) - 1);
  modifiablePath[sizeof(modifiablePath) - 1] = '\0';

  char *myPtr = strtok(modifiablePath, ":");

  while(myPtr != NULL)
  {
    snprintf(binPath, sizeof(binPath), "%s/%s", myPtr, command);

    if(access(binPath, X_OK) == 0)
    {
      return binPath;
    }

    myPtr = strtok(NULL, ":");
  }
  return NULL;
}

void historyBufferFree(char *historyBuffer[])
{
  for(int i = 0 ; historyBuffer[i] != NULL ; i++ )
  {
    free(historyBuffer[i]);
    historyBuffer[i] = NULL;
  }
}