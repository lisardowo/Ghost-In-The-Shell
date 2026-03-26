#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char userInput[120];

int main()
{
  while(true)
  {
    setbuf(stdout, NULL);

    printf("$ ");

    fgets(userInput, 100, stdin);

    size_t strLen = strlen(userInput);
    if(strLen > 0 && userInput[strLen - 1] == '\n')
    {
        userInput[strLen - 1] = '\0';
    }
    

    if(strcmp("exit", userInput) == 0)
    {
      return false;
    }
    else if(strncmp("echo ", userInput, 5) == 0)
    {
      printf("%s\n", userInput + 5);
    }
    else
    {
      printf("%s : command not found\n", userInput);
    }
  }
}
