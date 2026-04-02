
#include "getHistory.h"

static off_t get_file_size_posix(const char *filename);

void addHistory(char *command, int *historyCount, char *historyBuffer[])
{
    if(command[0] == '\0')
    {
        return;
    }

    if (*historyCount > 0 && strcmp(historyBuffer[*historyCount - 1 ], command) == 0)
    {
        return;
    }

    if(*historyCount < 10000)
    {
        
        historyBuffer[*historyCount] = strdup(command);
        (*historyCount) ++;

    }
}

void dumpHistory(int historyCount, char *historyBuffer[])
{

    int historyFd = creat("historyFile.txt", 0644);
    
    //size_t written = write(historyFd, historyBuffer, sizeof(*historyBuffer)); // this gonna get some erros, try an aproach with temp buf + sprintf
    for(int i = 0 ; historyBuffer[i] != NULL ; i++)
    {
        dprintf(historyFd, "%d  %s", i + 1 , historyBuffer[i]);
    }

}

void getHistory(int *historyCount, char *historyBuffer[])
{
    int historyFd = open("historyFile.txt", O_RDONLY , 0644);
    read(historyFd, historyBuffer, get_file_size_posix("historyFile.txt")); //this gona produce sum bugs TODO
}

static off_t get_file_size_posix(const char *filename) //snippet straight up stolen from internet
{
    struct stat st; 
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
}
