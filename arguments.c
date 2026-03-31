

#include "arguments.h"
#include "quotationParser.h"

static char argvStorage[10000];
char *argv[100];
int mode;

void ArgumentExtractor(char *userInput, int argumentCount, int mode)
{
	switch(mode)
	{
		case normal:
			normalExtractor(userInput, argumentCount);
			break;
		case singleQuote:
			singleExtractor(userInput, argumentCount);
			break;
		case doubleQuote:
			doubleExtractor(userInput, argumentCount);
			break;

	}
}

void normalExtractor(char *userInput, int argumentCount)
{
	normalExtractor(userInput, argumentCount);
}
void singleExtractor(char *userInput, int argumentCount)
{
	
}
void doubleExtractor(char *userInput, int argumentCount)
{
	
}


void argumentExtractor(char *userInput, int argumentCount)
{
  
  char arguments[10000];
  char joinedArguments[10000];
  bool quoted = false;
  char quoteChar = '\0';
  int i = 0;
  int storagePosition = 0;

  strncpy(arguments, userInput, sizeof(arguments));
  arguments[sizeof(arguments) - 1] = '\0';
  joinedArguments[0] = '\0';

  spacesInQuotes(arguments);

  char *token = strtok(arguments, " ");
  while(token != NULL && i < argumentCount)
  {

    if(!quoted)
    {
	
      size_t len = strlen(token);
      bool startQuoted = token[0] == '\'' || token[0] == '\"';
      bool closedInToken = (len > 1 && token[len - 1 ] == token[0]);

      if (startQuoted && !closedInToken)
      {
      
        quoted = true;
        quoteChar = token[0];
        strncpy (joinedArguments, token , sizeof(joinedArguments) - 1);
        joinedArguments[sizeof(joinedArguments) - 1] = '\0';

      }

    else
    {
	  restoreSpaces(token);
	  removeQuotes(token);

	  size_t tokenLen = strlen(token);

	  if(storagePosition + (int)tokenLen + 1 >= (int)sizeof(argvStorage))
	  {
		break ;
	  }


      argv[i] = &argvStorage[storagePosition];
      memcpy(argv[i], token, tokenLen + 1);
	  storagePosition += (int)tokenLen + 1;
      i++;

    }

  }
   else
  {
	size_t room = sizeof(joinedArguments) - (strlen(joinedArguments) - 1);
	if (room > 0)
	{
		strncat(joinedArguments, " ", room);
	}

	room = sizeof(joinedArguments) - (strlen(joinedArguments) - 1);
	if (room > 0 )
	{
		strncat(joinedArguments, token, room);

	}

	size_t len = strlen(token);
	if (len > 0 && token[len - 1] == quoteChar)
	{
		quoted = false;
		quoteChar = '\0';

		removeQuotes(joinedArguments);

		size_t joinedArgumentsLen = strlen(joinedArguments);

		if ((storagePosition + (int)joinedArgumentsLen + 1) >= (int)sizeof(argvStorage))
		{
			break;
		}

		argv[i] = &argvStorage[storagePosition];
		memcpy(argv[i], joinedArguments, joinedArgumentsLen + 1);
		storagePosition += (int)joinedArgumentsLen + 1;
		i ++;

		joinedArguments[0] = '\0';

	}

	

  }
    
  token = strtok(NULL, " ");

  }
  argv[i] = NULL;
}

void argumentCounter(char *userInput, int* argumentCount)
{
  char activeQuote = '\0';	
  bool inToken = false;
  *argumentCount = 0;
  for(int i = 0 ; userInput[i] != '\0' ; i++)
  {
    if (userInput[i] == '\'' || userInput[i] == '\"')
    {
      if (activeQuote == '\0')
	  {
		activeQuote = userInput[i];
		if(!inToken)
		{
			inToken = true;
			(*argumentCount)++;
		}
	  }
	  else if (activeQuote == userInput[i])
	  {
		activeQuote = '\0';
	  }
	  continue;
    }
    if (userInput[i] == ' ' && activeQuote == '\0')
    {
      inToken = false;
    }
	else if (!inToken)
	{
		inToken = true;
		(*argumentCount )++;
	}

  }
  

}

