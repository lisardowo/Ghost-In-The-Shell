#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lineEdition.h"
#include "binariesManager.h"
#include "arguments.h"
#include "inputManager.h"
#include "getHistory.h"
#include "utils.h"
#include "builtIn.h"

void createPrompt();
void REPL();
char *historyBuffer[10000];
int historyCount;
char prompt[1024];

int main()
{
  
  setbuf(stdout, NULL);
  
  REPL();

  return 0;
 
}

void REPL()
{
  createPrompt();
  availableCommands commandsList;
  fillCommands(&commandsList);
  getHistory(&historyCount, historyBuffer);

  while (true)
  {


    //set up
    memset(argv,0,sizeof(argv));
    int argumentCount = 0;
    bool redirectedstdout = false;
    bool redirectedstderr = false;
    bool appendStdOut = false;
    bool appendStdErr = false;
    char *stdoutPath = NULL;
    char *stderrPath = NULL;
    char *stdoutAppendPath = NULL;
    char *stderrAppendPath = NULL;

    int andSegment = 0;
    int andPosition = 0;
    //actuall terminal stuff
    readLineTab(prompt, &commandsList, userInput, sizeof(userInput), &historyCount, historyBuffer);
    //manage input
    sanitizeInput(userInput);
    addHistory(userInput, &historyCount, historyBuffer);
    argumentCounter(userInput, &argumentCount);
    argumentExtractor(userInput, argumentCount);

    char *segments[64][100];


    
    if (argv[0] == NULL)
    {
      continue;
    }



//it was efectively erased lol
  for(int i = 0 ; argv[i] != NULL ; i++)
  {
    //echo  >   eas 2>  ead
    //tok0 op0  tok1 op1 tok2
    //ls -lh > test.txt
    //tok tok op tok
   
    if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "1>") == 0)
      {
        if (argv[i + 1] == NULL)
        {
          printf("syntax error: expected file after '>'\n");
          redirectedstdout = false;
          stdoutPath = NULL;
          break ;          
        }
        else
        {

          redirectedstdout = true;
          stdoutPath = argv[i + 1];

          i++;
          continue;
        }
         
      }
      else if (strcmp(argv[i], "2>") == 0)
      {
        if (argv[i + 1] == NULL)
        {
          
          printf("syntax error: expected file after '2>'\n");
          redirectedstderr = false;
          stderrPath = NULL;
          break ;          
       
        }
        else
        {
        
          redirectedstderr = true;
          stderrPath = argv[i + 1];
          i++;
          continue;

        }
      }
      else if (strcmp(argv[i], ">>") == 0) // appendstdout
      {
        if (argv[i + 1] == NULL)
        {
          printf("syntax error: expected file after '>>'\n");
          appendStdOut = false;
          stdoutAppendPath = NULL;   
          break;    
        }
        else
        { 

          appendStdOut = true;
          stdoutAppendPath = argv[i + 1];
          i++;
          continue;

        }
      }
      else if (strcmp(argv[i], "2>>") == 0) // appendstderr
      {
        if (argv[i + 1] == NULL)
        {
          printf("syntax error: expected file after '2>>'\n");
          appendStdErr = false;
          stderrAppendPath = NULL;
          break;
        }
        else
        {
          
          appendStdErr = true;
          stderrAppendPath = argv[i + 1];
          i++;
          continue;
        
        }
        
      }
      

       else if (strcmp(argv[i], "&&") == 0)
      {
        if (argv[i + 1] == NULL)
        {
          printf("Esto deberia dejar escribir en multiples lineas\n");
          break;
                 
        }

        if (andPosition == 0 )
        {
          printf("Syntax error near unexpected token '&&'\n");
          break;
        }

        segments[andSegment][andPosition] = NULL;
        andSegment ++;
        andPosition = 0;
        
        continue;

      }
  segments[andSegment][andPosition++] = argv[i];

}

//for (int i = 0 ; commandToken[i] != NULL ; i++ ) printf("%s", commandToken[i]);;
  segments[andSegment][andPosition] = NULL;
  int segmentCount = andSegment + 1;


  int lastStatus = 0 ;

  for (int v = 0 ; v < segmentCount ; v++)
  {
    char **current = segments[v];
    if (current[0] == NULL)
    {
      lastStatus = 1 ;
      break ; 
    }

    if(v > 0 && lastStatus != 0)
    {
      break;
    }

    if(strcmp("exit", current[0]) == 0)
    {
        dumpHistory(historyBuffer);
        return;
    }


    else if(strcmp("echo", current[0]) == 0 && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
    {
      for (int i = 1 ; current[i] != NULL ; i++)
      {
        printf("%s", current[i]);
      }
      printf("\n");
      lastStatus = 0;
    }



    else if(strcmp("cd", current[0]) == 0 && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
    {
      
      if (current[1] == NULL || strcmp ("~", current[1]) == 0 )
      {
        char *homePath = getenv("HOME");
        lastStatus = (chdir(homePath) ) ? 0 : 1;
      }
      else
      {
        if (chdir(current[1]) != 0)
        {
          printf("%s: no such file or directory : \"%s\" ", current[0], current[1]);
          lastStatus = 1;
        }
        else
        {
          lastStatus = 9;
        }
      }

    }


    else if(strcmp("pwd", current[0]) == 0 && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
    {
      char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)))
      {
        printf("%s\n",cwd);
        lastStatus = 0;
      }
      else
      {
        lastStatus = 1;
      }
    }


    else if(strcmp("history", current[0]) == 0 && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
    {
      for(int i = 0 ; historyBuffer[i] != NULL ; i++)
      {
        printf("%d %s\n", i + 1, historyBuffer[i]);
      }
      lastStatus = 0;
    }


    else if(strcmp("type", current[0]) == 0 )
    {
      if(!redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
      {
        type(current, redirectedstdout, redirectedstderr, appendStdOut, appendStdErr, stdoutPath, stderrPath, stdoutAppendPath, stderrAppendPath) ;
      }
      else
      {//TODO THIS IS GON BE UGGLY SORRY -> turn this into a function
          if(stdoutPath)
          {
            int fileDescriptor = getFileDescriptor(stdoutPath , O_TRUNC | O_CREAT | O_WRONLY);
             if (current[1] == NULL)
              {
                dprintf("Usage : type <command>\n") ;
                lastStatus = 1;
              }
              else if((!strcmp("echo", current[1]) || !strcmp("exit", current[1]) ||
             !strcmp("type", current[1]) || !strcmp("pwd", current[1]) ||
             !strcmp("cd", current[1]) || !strcmp("history", current[1])) && !redirectedstdout && !redirectedstderr && !appendStdErr && !appendStdOut)
             {
             dprintf("%s is a shell builtin\n", current[1]);
             lastStatus = 0;
             }
      else
      {
        char *path = getPath(current[1]);
        if (path != NULL)
        {
          dprintf("%s is %s\n", current[1], path);
          lastStatus = 0;
        }
        else
        {
          printf("%s: not found\n", current[1]);
          lastStatus = 1;
        }
        }
          }
          
          if(stderrPath)
          {
            int fileDescriptor = getFileDescriptor(stderrPath, O_TRUNC | O_CREAT | O_WRONLY);
            
            lastStatus = 1;
          }

          if(appendStdOut)
          {
            int fileDescriptor = getFileDescriptor(appendStdOut, O_APPEND | O_CREAT | O_WRONLY);
          }

          if(appendStdErr)
          {
            int fileDescriptor = getFileDescriptor(appendStdErr, O_APPEND | O_CREAT | O_WRONLY);
          }
      }
    }

    else
    {
      lastStatus = executeBin(stdoutPath, stderrPath, stdoutAppendPath, stderrAppendPath, redirectedstdout, redirectedstderr, appendStdOut, appendStdErr, current);
    }


  }

}
}