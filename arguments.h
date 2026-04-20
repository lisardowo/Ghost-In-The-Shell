
#pragma once

#include <glob.h>
#include <string.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* sanitizeInput(char* userInput);

extern char **argv;
extern char userInput[10000];

void argumentCounter(char *userInput, int* argumentCount);
void argumentExtractor(char *userInput);
void expandGlobs(char *argv[]);
bool toogleState(bool state);
bool toogleQuotes(bool activeQuotes);
void removeQuotes(char *token);
void restoreSpaces(char *userInput);
void spacesInQuotes(char *userInput);
void expandArguments(char *argv[]);
