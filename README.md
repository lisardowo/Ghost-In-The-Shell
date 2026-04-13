# Ghost in the shell

Completely functional linux shell written from scratch, no extern libraries used. Project created with the purpose of understand better operative systems and masterize my C abilities, this project implement system calls, dynamic memory, parsing and file descriptors to assure an stable experience across devices.

When the project is completed, another branch will be opened in which a highly vulnerable shell would be in development following the idea behind "Damn Vulnerable Web Services" and other cibersecurity projects. 

This readme file documents the functional and secure version, the purpose behind such extensive documentation is either look for knoledge gaps when trying to break the vulnerable version or look how original version is thought in order to apply patches to sanitize vulnerable version.

This is not the best work but at least works.

## Index

1. [Purpose and Architecture](#1-purpose-and-architecture)
2. [Dependencies](#2-dependencies)
3. [Public API (headers)](#3-public-api-headers)
4. [Functional Behavior Summary](#4-functional-behavior-summary)
5. [Extending behavior](#5-extending-behavior)
6. [Current Known Gaps](#6-current-known-gaps)
7. [Installation and Quick Test](#7-installation-and-quick-test)

## Project Origin

Ghost in the shell is born out of curiosity about how OS internally work, impulsed by my recent interest in cibersecurity and systems explotation, the program is also thought to have a vulnerable verstryinion that can be easily exploited in systems as metasploitable or similar, granting another way to practice security system by re-parching the vulnerable shell to a most stable version with less risk

## 1. Purpose and Architecture

Main pipeline:

1. Prompting the user.
2. Receive input .
3. Tokenize the input via parsing (similar to how argc and argv work in a main function) and sanitize.
4. search for argv[0] (command) either in PATH or builtin.
5. Execute command passing the other elements in argv as arguments.

Modules:

- `arguments.*`: Parsing and extraction of the arguments that are written in prompt.
- `binariesManager.*`: Module in charge to find and execute binaries.
- `completition.*`: Logic behind autocomplete of input when pressing TAB.
- `inputManager.*`: Implementation of the prompt functions, directly related to completition.
- `lineEdition.*`: Implementation of the completition module, recieving the autocompleted commands and replacing the in terminal input, highly depends in "input manager" and "completition" modules.
- `quotationParser.*`: Parser that detects and interpret input inside quotation.

## 2. Dependencies


### 2.1 C standard library dependencies

- `stdio.h`
- `string.h`
- `stdint.h`
- `unistd.h`
- `fnctl.h`
- `stdbool.h`
- `stdlib.h`

### 2.3 Internal module dependencies

- `main.c` depends on: `lineEdition.h`, `binariesManager.h`,`arguments.h`,`inputManager.h`,`completition.h`
- `lineEdition.c` depends on: `lineEdition.h`, `completition.h`
- `binariesManager.c` depends on: `binariesManager.h`, `arguments.h`
- `arguments.c` depends on: `arguments.h`, `quotationParser.h`
- `inputManager.c` depends on: `inputManager.h` //TODO Prolly will remove inputManager in future versions
- `Completition.c` depends on: `completition.h`
- `quotationParser.c` depends on: `quotationParser.h`
- `utils.c` depends on: `quotationParser.h`
- `getHistory.c` depends on: `quotationParser.h`


## 3. Public API (headers)

This section lists all functions declared in headers (expected API surface).

### 3.1 `arguments.h`

- `void argumentCounter(char *userInput, int* argumentCount);`
  - Counts the arguments given in the prompt based in the spaces, if part of the string is quoted then counts as just one argument.
- `vvoid argumentExtractor(char *userInput, int argumentCount);`
  - based in argument count, tokenize the arguments and stores them to a argument vector variable
- `bool toogleState(bool state);`
  - utility function for is quoted logic (used in a primitive version) no longer in use for most code base


### 3.2 `binariesManager.h`

- `char* getPath(char *command);`
  - if a command(argv[0]) is not a built-in function then program looks for it in PATH variable and if found returns the dir of the binary .
- `void executeBin(char *stdoutPath,char *stdErrPath, bool redirectedstdout, bool redirectedStdErr, bool appendStdOut, bool appendStdErr, char *argv[]);`
  - First six parameters are "flags" that controls if the output of given  binary has to be redirected (">" operator) or will display in stdout, last parameter is the full (already tokenized) input (argv). Function forks the procces and executes the binary which addres is given by getPath(), when done child fork collapses to his father, father keeps waiting to that collapse to continue

### 3.3 `completition.h`

- `typedef struct{} available commands;`
  - Struct that store all availableCommands system-wide for the autocomplete function, elements of the object are : 
  * char **items; -> array of strings that are all the commands found
  * size_t count; -> how many commands are in the struct
  * size_t cap; -> Represents the maximum count of commands (used mainly to realloc memory for the structure in order to hold all the commands that can be found)

- `bool startCommandsList(availableCommands *list);`
  - Creates an instance of the struct and initialize its elements to 0/NULL.
- `void commandsFree(availableCommands *list);`
  - Set tha values of the struc to 0/NULL then frees the memory efectively deleting previouse instance
- `bool commandListGrow(availableCommands *list);`
  - If commands surpase the limit of list->cap, function dupes cap size via realloc
- `bool commandListAdd (availableCommands *list, char *command);`
  - utility function that adds provided command to the list
- `int compareCommands(const void *a,const void *b);`
  - utility function for qsort, used in Sanitize process
- `void commandListSanitize(availableCommands *list);`
  - Adding to the current list is made in a quick, messy way. Sanitize sorts commands alphabetically and looks for duplicates, if found duplicates are deleted
- `bool getBuiltIns(availableCommands *list);`
  - function that provides the built-ins for the list to be filled.
- `bool getBins(availableCommands *list);`
  - function that provides the binariesPath for the list to be filled.
- `bool fillCommands(availableCommands *list);`
  - utility function that takes as input the filled but unorder list and sanitize it via commandListSanitize().
- `size_t lengestCommonPrefix(char **matches, size_t count);`
  - detect the longest common prefix, used for autocompletition logic
- `size_t prefixMatches (availableCommands *list, char *prefix, char ***matches);`
  - Count how many commands has the same prefix and store them in a matches array
- `bool startWith(char *word, char *prefix);`
  - utility function that checks if the two parameters have the same letter and until what point they are equal

### 3.4 `inputManager.h`

- `char* sanitizeInput(char* userInput);`
  - replaces new line with null terminator of the provided input


### 3.5 `lineEdition.h`

- `void readLineTab(char *prompt, availableCommands *list, char *out, size_t outSize);`
  - Uses the other functions to read dinamically and exchange buffers when autocompleted
- `void firstToken(char *buf, char *out, size_t outSize);`
  - gets only the first token in the buffer.
- `void redraw(char *prompt, char *buf);`
  - redraws the whole propmt line to the user.
- `void disableRaw(void);`
  - disable raw mode and goes back to std configuration.
- `bool enableRaw(void);`
  - changes terminal to raw mode, capturing keys instantenously.

### 3.6 `quotationParser.h`

- `void removeQuotes(char *token);`
  - remove the quotes in a argument to use it properly
- `void restoreSpaces(char *userInput);`
  - restore the spaces replacing the arbtary value back to a space.
- `void spacesInQuotes(char *userInput);`
  - replace quoted spaces for an arbitary value in arguments so it can be counted as one .

###

## 4. Functional Behavior Summary

- readLineTab gets the input from user instantaneously so autocomplete can be triggered.
- sanitize and prepares input to use.
- compares argv[0] with builtin commands:
  - if argv is a builtin, command is executed 
  - if not, it looks for the command in PATH
  - if command exist, is executed, if not it raises an error

## 5 Extending behavior

this section explains how to add new features:

### 5.1 Design goals

  * Keep REPL stable and predictable
  * Avoid regressions in parsing
  * Keep execution behaviour consistent
  * keep changes small and isolated using modules (header files)

### 5.2 Main consideration points

  1. New built-in commands:
     - add builtin name to getBuiltins() completition module
     - Add command handling branch in REPL logic
     - Include in type checks

  2. Parsing:
     - Respect quote/escape semantics
     - Avoid exceed buffer limits: REMEMBER TO TERMINATE STRINGS WITH '\0'

  3. Binaries execution:
     - Keep child/parent responsibilities separated
     - Validate paths and operator before execution

### 5.3 how I think new features

  - Define feature scope and affected modules
  - Add a simple implementation
  - Run manual regression checks
  - Try to provoke a crash
  - Add specific cases handling
  - Update documentation
    

### 5.4 tests you can do when tweaking the program

  - Empty Input does not crash
  - Quoted arguments dont produce any unexpected behaviour
  - Unknown commands return expected errors
  - Builtins keep working
  - Tab completion still works
  - Redirections behave as supposed
  - Terminal works fluently



## 6 Current Known Gaps

  2. Current line editor does not support advanced editing
  3. Autocompletion is first token only, does not have any class of argument-aware/flags completion
  5. no config system
  6. some buffers are fixed size
  7. Error messages even tho are functional, some outpus are inconsistent in style and detail

## 7 Installation and Quick Test

### 7.1 Requirements 

```
  1. Linux enviroment
  2. gcc
  3. make
  4. cmake
  5. git
  
```

### 7.2 Clone

  In your terminal: 
```

  1. git clone https://github.com/lisardowo/Ghost-In-The-Shell.git
  2. cd Ghost-In-The-Shell

```
### 7.3 Build 
  
  In your terminal: 
  ```

  1. make

  ```

### 7.4 Run

In your terminal: 
```

./shell

```

### 7.5 Some quick tests

  1. pwd:
    Expected: print of current working directory
  2. echo hello world
    Expected: hello world
  3. type echo
    Expected: echo is a builtin
  4. ls
    Expected: all the content in current directory
  5. echo test > out.txt
    Expected: creates out.txt with "test" inside
  6. cat out.txt
    Expected: prints test
  7. history
    Expected: prints command history of the session
  8. exit
    Expected: executable stops cleanly

### 7.6 Troubleshooting
  1. Command not found for compiler tools:
    Install build tools package for your distro
  2. Build succeeds but shell does not run:
     Verify binary path and run from there
