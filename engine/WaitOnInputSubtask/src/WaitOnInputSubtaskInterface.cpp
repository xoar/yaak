#include "WaitOnInputSubtaskInterface.h"
#include "WaitOnInputSubtask.h"


/*define the struct. Just a wrapper for the cpp object*/
struct WaitOnInputStruct{
    WaitOnInputSubtask* subtask;
};


WaitOnInputStructPtr WaitOnInputConstructor (void* pluginList,
                                             int id,
                                             const char* eventName,
                                             const char* device,
                                             const char* specifier)
{
    WaitOnInputStructPtr subtask  =  
        (WaitOnInputStructPtr) malloc(sizeof(struct WaitOnInputStruct));
    
    subtask->subtask = new WaitOnInputSubtask((PluginList*) pluginList,
                                               id,
                                               std::string(eventName),
                                               std::string(device),
                                               std::string(specifier)
                                               );
    return subtask;
}

int WaitOnInputProcess(WaitOnInputStructPtr subtask)
{
    try
    {
      subtask->subtask->process();
    }
    catch (KillException& e)
    {
        /* if a kill was signaled return this
           to the caller so the thread can terminate*/
        
        /*free the ressource 
          because it was a heap allocation its not done automatically*/
        WaitOnInputDestructor(subtask);
        std::cout << "WaitOnINput recive kill signal"<< std::endl;
        return 0;
    }

    /*normal exit without a kill*/
    WaitOnInputDestructor(subtask);
    return 1;
}

void WaitOnInputDestructor(WaitOnInputStructPtr subtask)
{
    delete subtask->subtask;
    free(subtask);
}