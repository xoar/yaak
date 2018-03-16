#include "TriggerSubtaskInterface.h"
#include "TriggerSubtask.h"

/*define the struct. Just a wrapper for the cpp object*/
struct TriggerStruct{
    TriggerSubtask* subtask;
};

TriggerStructPtr TriggerConstructor(void* pluginList,
                                    int id,
                                    char * callerEventName)
{
    TriggerStructPtr subtask  =  (TriggerStructPtr) malloc(sizeof(struct TriggerStruct));
    
    subtask->subtask = new TriggerSubtask((PluginList*) pluginList,
                                          id,
                                          std::string(callerEventName));
    return subtask;

}

int TriggerProcess(TriggerStructPtr subtask)
{
    try
    {
      subtask->subtask->triggerNextSubtasks();
    }
    catch (KillException& e)
    {
        /* if a kill was signaled return this
           to the caller so the thread can terminate*/
        
        /*free the ressource 
          because it was a heap allocation its not done automatically*/
        std::cout << "Trigger recive kill signal"<< std::endl;
        TriggerDestructor(subtask);
        return 0;
    }

    /*normal exit without a kill*/
    TriggerDestructor(subtask);
    return 1;
}

void TriggerAddSubtask(TriggerStructPtr subtask,
                       const char* name, 
                       void (*eventfunc) () )
{
    subtask->subtask->addOutputSubtask(std::string(name),
                                       eventfunc);
}

void TriggerDestructor(TriggerStructPtr subtask)
{
    delete subtask->subtask;
    free(subtask);
}