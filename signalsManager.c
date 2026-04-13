
#include "signalsManager.h"


void ignoreSignalsInParent()
{

    struct sigaction ignoreAction;

    ignoreAction.sa_handler = SIG_IGN;
    ignoreAction.sa_flags = 0;
    sigemptyset(&ignoreAction.sa_mask);

    sigaction(SIGINT, &ignoreAction, NULL);
    sigaction(SIGQUIT, &ignoreAction, NULL);
    sigaction(SIGTSTP, &ignoreAction, NULL);

}

void restoreSignalsInChild()
{

    struct sigaction defaultAction;
    
    defaultAction.sa_handler = SIG_DFL;
    defaultAction.sa_flags = 0;
    sigemptyset(&defaultAction.sa_mask);
    
    sigaction(SIGINT, &defaultAction, NULL);
    sigaction(SIGINT, &defaultAction, NULL);
    sigaction(SIGINT, &defaultAction, NULL);

}