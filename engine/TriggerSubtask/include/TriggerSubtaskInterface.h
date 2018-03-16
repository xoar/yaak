#ifndef TRIGGERSUBTASKINTERFACE_H
#define TRIGGERSUBTASKINTERFACE_H


#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct TriggerStruct ;

typedef struct TriggerStruct * TriggerStructPtr;


TriggerStructPtr TriggerConstructor(void* pluginList,
                                    int id,
                                    char * callerEventName);
int TriggerProcess(TriggerStructPtr subtask);
void TriggerAddSubtask(TriggerStructPtr subtask,
                       const char* name, 
                       void (*eventfunc) () );
void TriggerDestructor(TriggerStructPtr subtask);

#ifdef __cplusplus
}
#endif

#endif