#ifndef TASKMANAGER_H_INCLUDED
#define TASKMANAGER_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::vector
#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>
#include "Utils.h"
#include "GameEnginePlugin.h"
#include "Task.h"
#include "Subtask.h"

#include "ReloadGamePlugin.h"
#include "PluginList.h"

#define TASKMANAGERNAME ("TaskManager")

class Task;

/* signals a kill of the current thread*/
class KillException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "kill exception was thrown\n";
    }
};

class TaskManager : public GameEnginePlugin
{

  /* there are three possibilities for the status of a task in the Taskmanager:
   * active: The task currently runs.
   * supsend: the task is supsended and will be resume in the next round.
   * waiting: a task with the same name is currently running.
   *          the new task will be proccessed when the old one terminates
   */

  /*A task and a event in the language are nearly the same. 
    every event has one task*/

  public:

    TaskManager(PluginList* pluginList);

    /* add a task to process it. try to add it to the active list and
     * run it directly. If there already runs a task with the
     * same name the new task will be add to the waiting list, until the
     * old is finished. not block.
     */

    /* callerEventName: the callers event name.
     * Is used to check if the event(Task) was killed.
     * For calls without this check use ""
     */

    /* throw an exception if the caller was killed.
     * Used to disable branching of killed Task */
    void addTask(Task* task,std::string callerEventName); //throw (KillException);

    /* suspend a task until the next loop iteration*/
    void suspendTaskUntilNextRound(std::string name); //throw (KillException);

    /*remove the task from the active task list and free the task ressource*/
    void removeTask(std::string name);

    /* suspend a task until the next loop iteration*/
    void suspendTaskUntilNextRound(Task* task); //throw (KillException);

    /*remove the task from the active task list */
    void removeTask(Task* task);

    /* add a task for the next round. add as a waiting task*/
    void addTaskForNextRound(Task* task);

    /* signal next round and waits until all task of this round where scheduled*/
    void process();

    /* signal a kill of all the task except those one in the given list*/
    /* param nameList a list of event names*/
    void killAllTaskExcept(std::vector<std::string> & nameList); 

    /* get the loop counter.
     * every loop has a number. not protected against overflows. 
     * use only != for checks
     */
    int getLoopCounter();

    virtual std::string getName() {return getPluginName();}
    static std::string getPluginName() {return TASKMANAGERNAME;}

  protected:

    /*helper function: 
      find a task with the given name in the active and suspended list.
      returns nullptr if not found.
      should be called with an auqired mutex*/
    Task* getTaskByName(std::string name);

    /*helper function. check if the task is already running.
      when true the task should be added to the waiting list.
      should be called with an auqired mutex*/
    bool isTaskInList(std::vector<Task*>* list ,std::string name);

    /*helper function. delete all occurrence of a task with the given name 
      in the list.
      should be called with an auqired mutex*/
    void removeTaskFromList(std::vector<Task*>* list ,std::string name);

    /* Check if all tasks finish their work.
    if true it notify the process thread that the next round can start.
    should be called with and aqquired mutex*/
    void CheckAllTasksDone();

    /* Check if all selected tasks got killed.
    if true it notify the the waiting kill function.
    should be called with and acquired mutex*/
    void CheckAllSelectedActiveTasksGotKilled();


    /* try to process all waiting thread. 
    if they are still not runnable ithey will be add to the waiting list again*/
    void processWaitingThreads();

    void processSupsendedThreads();

    /*active and suspended tasks are managed in this list. 
      waiting threads are in the waiting TaskList*/
    std::vector<Task*>* taskList;

    /* List for the waiting tasks*/
    std::vector<Task*>* waitingTaskList;

    /*list of terminated task to prevent calls like a->b->a in one round*/
    std::vector<Task*>* terminatedTaskList;


    /* counter for the active threads*/
    int activeTaskCounter;

    /* counter for the supsended threads*/
    int suspendedTaskCounter;

    /* counter for the waiting threads*/
    int waitingTaskCounter;

    /*counter for the number of active tasks 
      which should are left to be killed in this round*/
    int leftToKillActiveTaskCounter;

    /* mutex to prevent more than one thread could enter the task manager.
       TODO: the recursive attribute is only needed by the processWaitingThreads
       routine. if you want to speed this up rewrite it and change the mutex
       to a standard mutex*/
    std::recursive_mutex taskManagerMutex;

    /*TODO: could be replace be a normal contition variable when using
      a non recursive mutex*/
    std::condition_variable_any nextRound;
    std::condition_variable_any allActiveTaskAreDone;

    /* when there was a killActiveTask call, the function blocks until
       all task are selected active task got killed*/
    std::condition_variable_any allSelectedActiveTaskGotKilled;

    /*every process iteration has a loop number */
    /*for checks against this number: has an overflow so only != checks
      are adbvisable */
    int loopCounter;


    /* pointer to the reload plugin*/
    /* if the reload Plugin signals a realod we throw an exception*/
    ReloadGamePlugin* reloadPlugin;


};

#endif // TASKMANAGER_H_INCLUDED
