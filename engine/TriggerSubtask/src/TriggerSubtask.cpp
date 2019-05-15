#include "TriggerSubtask.h"

TriggerSubtask::TriggerSubtask(PluginList* pluginList,
                               int id,
                               std::string eventName)
                               : Subtask(id)
{
    outputTaskList = new std::vector<Task*>();
    taskManager = ((TaskManager*) pluginList->get("TaskManager"));
    this->eventName = eventName;
}

/** just fire the next node */
void TriggerSubtask::process()
{
    triggerNextSubtasks();
}


void TriggerSubtask::addOutputSubtask(std::string name, void (*eventfunc) ())
{
    Task* task = new Task(taskManager,name,eventfunc);
    outputTaskList->push_back(task);

}

void TriggerSubtask::triggerNextSubtasks()
{
    /** when we remove the task before triggering the new one and this is the only active task
     the taskmanager could start a new round after remove the task.

     so first trigger all and the remove yourself(done through the compiler)
     */

    for (std::vector<Task*>::iterator it = outputTaskList->begin();
         it != outputTaskList->end(); it++)
    {
        Task* task = (*it);
        /*add and run task*/
        taskManager->tryToSpawnTask(task,eventName);

    }
    
}
