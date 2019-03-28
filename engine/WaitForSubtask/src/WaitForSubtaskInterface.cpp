#include "WaitForSubtaskInterface.h"

/*include the cpp variant*/
#include "WaitForSubtask.h"


/*define the struct. Just a wrapper for the cpp object*/
struct WaitForSubtaskStruct{
    WaitForSubtask* subtask;
};

/* the Constructor*/
WaitForSubtaskStructPtr WaitForSubtaskConstructor(void* pluginList,
                                         int id,
                                         const char* eventName)
{

    //struct WaitForStruct subtask;

    WaitForSubtaskStructPtr subtask  =  (WaitForSubtaskStructPtr) malloc(sizeof(struct WaitForSubtaskStruct));

    subtask->subtask = new WaitForSubtask((PluginList*) pluginList,
                                         id,
                                         std::string(eventName));
    return subtask;

}

/** this is the process function which must be overriden
    to implement the disired functionality */

int WaitForSubtaskProcess(WaitForSubtaskStructPtr subtask)
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
        std::cout << "WaitFor recive kill signal" << std::endl;
        WaitForSubtaskDestructor(subtask);
        return 0;
    }

    /*normal exit without a kill*/
    WaitForSubtaskDestructor(subtask);
    return 1;
}

/*getter and setter*/
void WaitForSubtaskSetTime(WaitForSubtaskStructPtr subtask,double time)
{
    subtask->subtask->setTime(time);
}

void WaitForSubtaskDestructor(WaitForSubtaskStructPtr subtask)
{
    delete subtask->subtask;
    free(subtask);
}