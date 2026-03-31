

#include "quotationParser.h"

bool toogleQuotes(bool activeQuotes)
{
    
    return !activeQuotes;
}

void removeQuotes(char *token)
{
   char *src = token; // Pointer to read
    char *dst = token; // Pointer to write

    while (*src) {
        if (*src != '\"' && *src != '\'') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // Null-terminate the new string
}

void spacesInQuotes(char *userInput)
{
	bool inQuote = false;

	for (int i = 0 ; userInput[i] != '\0' ; i++)
	{
		if (userInput[i] == '\'' || userInput[i] == '\"')
		{
			inQuote = toogleQuotes(inQuote);
		}
		if(userInput[i] == ' ' && inQuote)
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