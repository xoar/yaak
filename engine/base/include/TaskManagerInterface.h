#ifndef TASKMANAGERINTERFACE_H
#define TASKMANAGERINTERFACE_H

#ifdef __cplusplus
extern "C" 
{
#endif

/*for fast prototyping we use this as a workaround*/
void AddAndRunTask (void * pluginList,const char* name,void (*run) (),
                    char *callerEventName);
void RemoveTask (void * pluginList,const char* name);
int SuspendTaskUntilNextRound(void * pluginList,const char* name);
void AddTaskForNextRound(void * pluginList,const char* name,
                         void (*run) ());

void KillAllTasks(void * pluginList);
void KillAllTasksExcept(void * pluginList,const char* eventName);

#ifdef __cplusplus
}
#endif

#endif