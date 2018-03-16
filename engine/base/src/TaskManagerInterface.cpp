#include "TaskManagerInterface.h"
#include "TaskManager.h"
#include "PluginList.h"

/*for fast prototyping we use this as a workaround*/
void AddAndRunTask (void * pluginList,const char* name,
                    void (*run) (),
                    char *callerEventName)
{
    //starter event
    PluginList* mPluginList = (PluginList*) pluginList;
    TaskManager* taskManager = ((TaskManager*) mPluginList->get("TaskManager"));
    Task* task = new Task(taskManager,std::string(name), run);
    taskManager->addTask(task,std::string(callerEventName));

}

void RemoveTask (void * pluginList,const char* name)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    TaskManager* taskManager = ((TaskManager*) mPluginList->get("TaskManager"));
    taskManager->removeTask(std::string(name));
}

int SuspendTaskUntilNextRound(void * pluginList,const char* name)
{
    try
    {
        PluginList* mPluginList = (PluginList*) pluginList;
        TaskManager* taskManager = ((TaskManager*) mPluginList->get("TaskManager"));
        taskManager->suspendTaskUntilNextRound(std::string(name));
    }
    catch (KillException& e)
    {
        /* if a reload was signaled return this
           to the caller so the thread can terminate*/
        return 0;
    }

    /*has blocked normally*/
    return 1;

}

void AddTaskForNextRound(void * pluginList,const char* name,void (*run) ())
{
    PluginList* mPluginList = (PluginList*) pluginList;
    TaskManager* taskManager = ((TaskManager*) mPluginList->get("TaskManager"));
    Task* task = new Task(taskManager,std::string(name), run);
    taskManager->addTaskForNextRound(task);

}

void KillAllTasks(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    
    /*create an empty namelist and kill all tasks*/
     std::vector<std::string> nameList;
    ((TaskManager*) mPluginList->get( TaskManager::getPluginName() ))->killAllTaskExcept(nameList);

}

void KillAllTasksExcept(void * pluginList,const char* eventName)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    
    /*create an empty namelist and kill all tasks*/
     std::vector<std::string> nameList;
     nameList.push_back(std::string(eventName));
     
    ((TaskManager*) mPluginList->get( TaskManager::getPluginName() ))->killAllTaskExcept(nameList);

}