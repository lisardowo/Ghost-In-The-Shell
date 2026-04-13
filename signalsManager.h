#pragma once

#include <signal.h>
#include <stddef.h>

void ignoreSignalsInParent();
void restoreSignalsInChild();