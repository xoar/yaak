#ifndef WAITONINPUTSUBTASKINTERFACE_H_INCLUDED
#define WAITONINPUTSUBTASKINTERFACE_H_INCLUDED

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct WaitOnInputStruct ;

typedef struct WaitOnInputStruct * WaitOnInputStructPtr;

WaitOnInputStructPtr WaitOnInputConstructor (void* pluginList,
                                             int id,
                                             const char* eventName,
                                             const char* device,
                                             const char* specifier);

int WaitOnInputProcess(WaitOnInputStructPtr subtask);

void WaitOnInputDestructor(WaitOnInputStructPtr subtask);

#ifdef __cplusplus
}
#endif

#endif