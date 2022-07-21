#ifndef CROSSPLAT_H
#define CROSSPLAT_H

#ifdef _WIN32

#include <windows.h>

#define cmd_clear "CLS"
//Create bindings for linux functions using windows functions
#define sleep(seconds) Sleep((seconds)*1000)
#define usleep(microseconds) Sleep((DWORD)(microseconds)/1000)

#elif defined(__linux__)

#include <unistd.h>
#include <pthread.h>

#define cmd_clear "clear"

#endif

#endif