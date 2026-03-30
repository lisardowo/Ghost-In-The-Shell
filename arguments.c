

#include "arguments.h"

char *argv[100];

void argumentExtractor(char *userInput, int argumentCount)
{
  char arguments[100000];
  strncpy(arguments, userInput, sizeof(arguments));
  arguments[sizeof(arguments) - 1] = '\0';
  
  char *token = strtok(arguments, " ");
  int i = 0;
  while(i < argumentCount)
  {
   
    argv[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  
}

void argumentCounter(char *userInput, int* argumentCount)
{
  *argumentCount = 1;
  for(int i = 0 ; userInput[i] != '\0' ; i++)
  {
    if (userInput[i] == ' ')
    {
      (*argumentCount) ++ ;
    }

  }
  

}
