#pragma once

#include <stdbool.h>
#include <string.h>




bool toogleQuotes(bool activeQuotes);
void removeQuotes(char *token);
void restoreSpaces(char *userInput);
void spacesInQuotes(char *userInput);