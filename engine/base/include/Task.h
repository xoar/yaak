#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <list>          // std::list
#include "Utils.h"
#include "TaskManager.h"
#include <PluginList.h>

class TaskManager;

class Task
{
  public:

    /**create a Task, a task has a name and a run function which it process.*/ 
    Task(TaskManager *taskManager,std::string name,void (*run) ());

    /** get its name. */
    std::string getName();
    /** set its name */
    void setName(std::string name);

    void (*run) ();

    void setWaiting();
    void setSuspended();
    void setActive();

    bool isWaiting();
    bool isSuspended();
    bool isActive();


    /*when you set the kill flag there is no chance to redeem it*/
    void setKilled();
    bool gotKilled();

    TaskManager * getTaskManager();

  protected:

    enum {ACTIVE,WAITING,SUSPENDED} status;

    /*signal that the task got killed. is independent from the status because 
      it can be killed when active but also when supsended*/
    bool killed;
    /** its name to find it in the availible task list */
    std::string name;
    /* pointer to the taskmanger*/
    TaskManager *taskManager;

};

#endif // TASK_H_INCLUDED
