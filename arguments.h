#pragma once

#include <stdlib.h>
#include <string.h>
#include "inputManager.h"

extern char *argv[100];
void argumentCounter(char *userInput, int* argumentCount);
void argumentExtractor(char *userInput, int argumentCount);

