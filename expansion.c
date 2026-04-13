
#include "expansion.h"

static char storage[1000];
static int storagePosition = 0;

static void resetStoragePosition() //TODO this would be better with an int type?
{
    storagePosition = 0;
}

void expandArguments(char *argv[])
{
    resetStoragePosition();

    for(int i = 0 ; argv[i] != NULL; i++)
    {
        if (argv[i] == NULL)
        {
            continue;
        }

        char *originalToken = argv[i];
        char tempBuffer[1000];
        int tempPosition = 0;
        bool isExpandible = false;

        for (int v = 0 ; originalToken[v] != '\0' ; v++)
        {
            if(originalToken[v] == '$' && originalToken[v+1] != '\0' && originalToken[v + 1] != ' ')
            {
            
                isExpandible = true;
                v++;

                char varName[100];
                int varPosition = 0;

                while ((originalToken[v] != '\0' && originalToken[v] >= 'a' && originalToken[v] <= 'z') || (originalToken[v] >= 'A' && originalToken[v] <= 'Z') || (originalToken[v] >= '0' && originalToken[v] <= '9') || (originalToken[v] == '_'))
                {
                    if(varPosition < (int)sizeof(varName) - 1)
                    {
                        varName[varPosition++] = originalToken[v];
                    }
                    v++;
                }
                varName[varPosition] = '\0';
                v--;
                
                char *envValue = getenv(varName);
                if(envValue != NULL)
                {
                    for(int k = 0 ; envValue[k] != '\0' ; k++)
                    {
                        if (tempPosition < (int)sizeof(tempBuffer) - 1)
                        {
                            tempBuffer[tempPosition++] = envValue[k]; 
                        }
                    }
                }
            }

            else
            {
                if(tempPosition < (int)sizeof(tempBuffer) - 1)   
                {
                    tempBuffer[tempPosition++] = originalToken[v];
                }
            }   
        }
                tempBuffer[tempPosition++] = '\0';

                if (isExpandible)
                {
                    int len = strlen(tempBuffer);
                    if((storagePosition + len) + 1 < (int)sizeof(storage))
                    {
                        strcpy(&storage[storagePosition], tempBuffer);
                        argv[i] = &storage[storagePosition];
                        storagePosition += (len + 1);
                    }
                }

            }
        }
