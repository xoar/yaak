#ifndef WAITFORSUBTASK_H
#define WAITFORSUBTASK_H

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct WaitForSubtaskStruct ;

typedef struct WaitForSubtaskStruct * WaitForSubtaskStructPtr;

/* the Constructor*/
WaitForSubtaskStructPtr WaitForSubtaskConstructor(void* pluginList,
			                                    int id,
			                                    const char* eventName);

/** this is the process function which must be overriden
    to implement the disired functionality */

int WaitForSubtaskProcess(WaitForSubtaskStructPtr subtask);

/*getter and setter*/

void WaitForSubtaskSetTime(WaitForSubtaskStructPtr subtask,double ptime);
void WaitForSubtaskDestructor(WaitForSubtaskStructPtr subtask);

#ifdef __cplusplus
}
#endif

#endif
