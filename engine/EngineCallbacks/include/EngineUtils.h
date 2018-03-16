#ifndef ENGINEUTILS_H
#define ENGINEUTILS_H

#include "stdio.h"


#ifdef __cplusplus
extern "C" 
{
#endif

void initPlugins (void* _pluginList);

void mainLoop(void* _pluginList);

#ifdef __cplusplus
}
#endif

#endif