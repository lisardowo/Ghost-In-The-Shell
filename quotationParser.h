#pragma once

#include <stdbool.h>



bool toogleQuotes(bool activeQuotes);
void removeQuotes(char *token);
void restoreSpaces(char *userInput);
void spacesInQuotes(char *userInput);