#ifndef TRIGGERNODE_H_INCLUDED
#define TRIGGERNODE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::vector
#include "Utils.h"
#include "Subtask.h"
#include "TaskManager.h"

class TriggerSubtask : public Subtask
{
    public:
    /* construct a trigger. eventName is the name of the calling event*/
    /* is "" when called by the system*/
    TriggerSubtask(PluginList* pluginList,int id,std::string eventName);

    /** function pointer to the next event. 
        the node can trigger several events*/
    void addOutputSubtask(std::string name, void (*eventfunc) () );

    virtual void process();

    /* call the next nodes */
    void triggerNextSubtasks();

    /** list of task which we trigger */
    std::vector<Task*>* outputTaskList;

    /** pointer to the taskManager to add and run the tasks*/
    TaskManager* taskManager;

    std::string eventName;

};

#endif // TRIGGERNODE_H_INCLUDED
