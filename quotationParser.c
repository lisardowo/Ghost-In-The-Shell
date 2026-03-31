

#include "quotationParser.h"


void removeQuotes(char *token)
{
    char activeQuote = '\0';
    char *src = token;
    char *dst = token;
    while (*src != '\0')
    {
        if ((*src == '\'' || *src == '"'))
        {
            if (activeQuote == '\0')
            {
                activeQuote = *src;
                src ++;
                continue;
            }
            if (activeQuote == *src)
            {
                activeQuote = '\0';
                src++;
                continue;
            }
        }

        *dst++ = *src++;
    }

    *dst = '\0';
    
}

void spacesInQuotes(char *userInput)
{
	char activeQuote = '\0';

	for (int i = 0 ; userInput[i] != '\0' ; i++)
	{
		if (userInput[i] == '\'' || userInput[i] == '\"')
		{
			if (activeQuote == '\0')
            {
                activeQuote = userInput[i];
            }
            else if( activeQuote == userInput[i])
            {
                activeQuote = '\0';
            }
            
		}

		if(userInput[i] == ' ' && activeQuote != '\0')
		{
			userInput[i] = 31;
		}
	}
}

void restoreSpaces(char *userInput)
{
	for (int i = 0 ; userInput[i] != '\0' ; i++)
	{

		if((unsigned char)userInput[i] == 31)
		{
			userInput[i] = ' ';
		}
	}
}