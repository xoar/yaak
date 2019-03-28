#include "TaskManager.h"
#include <algorithm> 


TaskManager::TaskManager(PluginList* pluginList)
{
    taskList = new std::vector<Task*>();
    waitingTaskList = new std::vector<Task*> ();
    terminatedTaskList = new std::vector<Task*> ();

    activeTaskCounter = 0;
    loopCounter = 0;
    suspendedTaskCounter = 0;
    waitingTaskCounter = 0;

    leftToKillActiveTaskCounter = 0;

    reloadPlugin = ((ReloadGamePlugin*) pluginList->get(ReloadGamePlugin::getPluginName() ));

}

int TaskManager::getLoopCounter()
{
    return loopCounter;

}


void TaskManager::suspendTaskUntilNextRound(Task* task) //throw (KillException)
{
    /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);
    
    /*check if the task got killed.
      because the task is active when it enters this function we
      have to decrease the left to kill counter TODO:check if active*/
    if (task->gotKilled()) leftToKillActiveTaskCounter--;

    //Check if the task is not suspended -> suspend him and change the counter.
    if( task->isActive() )
    {
        task->setSuspended();
        activeTaskCounter--;
    }
    //if it was already suspended or it was waiting this is strange...
    else
    {
        std::cerr << "WARNING: try to suspend an waiting/suspended task again"
                  << task->getName() << "\n";
    }

    /* add him to the suspended task counter*/
    suspendedTaskCounter++;

    /*all tasks are processed. notify next round*/
    CheckAllTasksDone();

    /*notify the kill function if all task were killed*/
    CheckAllSelectedActiveTasksGotKilled();

    /*if the task got killed we don't suspend him*/
    //TODO: add a new exception for this
    if (task->gotKilled())  throw KillException();

    nextRound.wait(lock);

    /* alive so resume*/

    /*set active but not inc the active task counter. 
      this is done in the process function to ensure 
      every resumed thread has run before a new round is notified
    */
    task->setActive();

    /*check if the task got killed.
      because this task was suspended we don't have to call
      CheckAllSelectedActiveTasksGotKilled() and decrease the leftactive counter
      but we have to set it active to decrease the active counter of the process round
      */
    if (task->gotKilled()) throw KillException();

}

/* Check if all tasks finish their work.
   if true it notify the process thread that the next round can start.
   should be called with and acquired mutex*/
void TaskManager::CheckAllTasksDone()
{

    if (activeTaskCounter <= 0)
    {
        activeTaskCounter = 0;
        allActiveTaskAreDone.notify_all();
    }

}

/* Check if all selected tasks got killed.
   if true it notify the the waiting kill function.
   should be called with and acquired mutex*/
void TaskManager::CheckAllSelectedActiveTasksGotKilled()
{

    if (leftToKillActiveTaskCounter <= 0)
    {
        leftToKillActiveTaskCounter = 0;
        allSelectedActiveTaskGotKilled.notify_all();
    }

}

void TaskManager::removeTask(Task* task)
{
    /* only one can access the manager */
    std::lock_guard<std::recursive_mutex> lock(taskManagerMutex);

#ifdef DEBUG_OUTPUT
    std::cout << "remove task: " << task->getName() 
              << " Loop : " << getLoopCounter() << "\n";
#endif
    
    if( task->isActive() )
    {
        activeTaskCounter--;
    }
    else
    {
        std::cerr << "WARNING: removed waiting/suspended task" 
                  << task->getName() <<"\n";
    }

    /* because the task will be removed we dont throw an exception.
       just decrease the counter and signal the kill function if neccessary*/
    if (task->gotKilled()) leftToKillActiveTaskCounter--;

    /*remove the task */

    /*find the position in the array*/
    std::vector<Task*>::iterator it;
    it = std::find(taskList->begin(), taskList->end(), task);

    if (it != taskList->end() )
    {
        /*now remove it*/
        taskList->erase(it);
    }
    else
    {
        std::cerr << "ERROR: cant remove task" << task->getName() 
        <<" its not in the tasklist\n";
        std::exit(EXIT_FAILURE);
    }
    
    /*prevent a second call of this task in this round*/
    terminatedTaskList->push_back(task);

    /*free the task ressource*/
    //delete task;

    /*notify the process thread if all task finished their work*/
    CheckAllTasksDone();

    //std::cout << " done" << std::endl;

    /*notify the kill function if all active task got killed*/
    CheckAllSelectedActiveTasksGotKilled();

    //std::cout << "remove done" << std::endl;

}

/*helper function. should be called with an auqired mutex*/
bool TaskManager::isTaskInList(std::vector<Task*>* list ,std::string name)
{
    for (std::vector<Task*>::iterator it = list->begin(); 
         it != list->end();
         it++)
    {
        if ((*it)->getName() == name)
        {
            return true;
        }
    }

    return false;

}

/*helper function. should be called with an auqired mutex*/
Task* TaskManager::getTaskByName(std::string name)
{
    Task * task = nullptr; 

    //std::cout << "getaskname " << name << ","<<(name == "")<< std::endl;

    for (std::vector<Task*>::iterator it = taskList->begin(); 
         it != taskList->end();
         it++)
    {
        task = *it;
        if (task->getName() == name)
        {
            return task;
        }
    }

    return nullptr;

}

/*helper function. should be called with an auqired mutex*/
void TaskManager::removeTaskFromList(std::vector<Task*>* list ,std::string name)
{
    try 
    {
        std::vector<Task*>::iterator nextIt;

        for (std::vector<Task*>::iterator it = list->begin();
             it != list->end(); it=nextIt)
        {
            if ((*it)->getName() == name)
                nextIt = list->erase(it);
            else
                nextIt= std::next(it);
        }
    }
    catch (std::exception& e)
    {
            std::cerr << "\n ERROR: cant remove task " << e.what() << '\n';
            std::exit(EXIT_FAILURE);
    }
}


void TaskManager::addTask(Task* task,std::string callerEventName) //throw (KillException)
{

     /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);

    
    /*check if the caller was killed. no branching is allowed for those*/
    /*"" is used by a call from the system*/
    Task* caller = getTaskByName(callerEventName);
    if (caller != nullptr)
    {   
        if (caller->gotKilled()) throw KillException();
    }

    /*ensure the task is not already in the list or ran in this round*/
    /*no task can be called twice in a loop. makes no scence*/

    /*search it in the task list and terminated task list*/

    /* we don't search for the task pointer but the task name,
     * because the task object can be created twice 
     * with the same task function.*/

    /* was the task in one of the lists?*/
    if ( (isTaskInList(taskList,task->getName())) ||
         (isTaskInList(terminatedTaskList,task->getName())) )
    {

        std::cerr << "WARNING: tried to add a task which is already in the list"
                  << ",taskname: " << task->getName() << getLoopCounter() << "\n";

        /*ensure the task is handled in the next round*/
        waitingTaskCounter++;
        waitingTaskList->push_back(task);
        task->setWaiting();
    }
    else
    {

#ifdef DEBUG_OUTPUT
            /* run task */
            std::cout << "run taks: " << task->getName()
                      << " Loop: " << getLoopCounter() << "\n";
#endif

            activeTaskCounter++;
            taskList->push_back(task);

            task->setActive();
            /*spawn the thread*/
            std::thread task_thread(task->run);

            task_thread.detach();
    }



}

void TaskManager::addTaskForNextRound(Task* task)
{

    /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);

    /* we used a waiting task and not a supsended because
       to suspend a task we need a started detached flow*/

    if ( isTaskInList(waitingTaskList,task->getName()))
    {

        std::cerr << "ERROR: task for the next round is already in the waiting list"
                  << ",taskname: " << task->getName() << getLoopCounter() << "\n";
        std::exit(EXIT_FAILURE);
    }
    else
    {
        /*ensure the task is handled in the next round*/
        waitingTaskCounter++;
        waitingTaskList->push_back(task);
        task->setWaiting();
    }


}


void TaskManager::suspendTaskUntilNextRound(std::string name) //throw (KillException)
{
    /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);

    for (std::vector<Task*>::iterator it = taskList->begin(); 
         it != taskList->end();
         it++)
    {
        if ((*it)->getName() == name)
        {
            Task* task = (*it);

            /*we have to unlock the mutex because this function will not
              return in this round*/
            lock.unlock();
            suspendTaskUntilNextRound(task);

            break;
        }
    }
}


void TaskManager::removeTask(std::string name)
{

    /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);

    for (std::vector<Task*>::iterator it = taskList->begin(); 
         it != taskList->end(); 
         it++)
    {
        if ((*it)->getName() == name)
        {   
            //lock.unlock();
            /*if you replace the recursive lock a unlock is neccessary here*/
            removeTask((*it));
            
            break;
        }
    }

    //std::cout << "remove done" << std::endl;
}

/* try to process all waiting thread. 
  if they are still not runnable ithey will be add to the waiting list again*/
void TaskManager::processWaitingThreads()
{
    /*make a copy of the waiting list and clean 
      it for trying to readd the tasks*/
    std::vector<Task*> waitList(*waitingTaskList);

    waitingTaskList->clear();
    waitingTaskCounter = 0;
    
    /* try to add every task again. 
     if its still not runnable it will be add to the waiting list again*/
    for (std::vector<Task*>::iterator it = waitList.begin(); 
         it != waitList.end(); 
         it++)
    {
        Task* task = (*it);
        /*add the task. use the recursive mutex*/
        addTask(task,"");
    }
}

void TaskManager::processSupsendedThreads()
{

    /* process the suspended threads:
     *   ensure that all resumed thread are processed before the next round
     *   by adding them to the active counter
     */
    activeTaskCounter += suspendedTaskCounter;
    suspendedTaskCounter = 0;

    /*wake up the suspended task*/
    nextRound.notify_all();

}

/* waits until all task of this round where scheduled*/

void TaskManager::process()
{
    //signal next round + wait for active Task
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);
    
    //inc the loop counter
    loopCounter++;

    /*clear the terminated task list for this round. prevent double call of a task*/
    terminatedTaskList->clear();

    /*process the suspended thread*/
    processSupsendedThreads();

    
    /*process the waiting thread*/
    processWaitingThreads();

    /*if there were no task to activate in this round check this before waiting*/

    /*we start waiting before the processing of the new tasks (start of the supsended
      and end of the active(remove function))
      because of the aquired mutex*/

    if (activeTaskCounter > 0)
    {
        /* wait until all task are processed*/
        allActiveTaskAreDone.wait(lock);
    }
}


 void TaskManager::killAllTaskExcept(std::vector<std::string> & nameList)
 {
    /* only one can access the manager */
    std::unique_lock<std::recursive_mutex> lock(taskManagerMutex);

    /*make a copy of the waiting list to delete the names from it*/
    std::vector<Task*> waitingTaskListCopy(*waitingTaskList);
    std::vector<Task*> taskListCopy(*taskList);

    std::cout << "search in list" << std::endl;

    for (auto it = nameList.begin(); it != nameList.end(); it++)
    {
        /* remove the name in the waiting (waitingList), 
           active and supended (taskList) list*/
        removeTaskFromList(&waitingTaskListCopy,(*it));
        removeTaskFromList(&taskListCopy,(*it));
    }

    std::cout << "set kill" << std::endl;

    /* signal the kill of the left tasks in both list
       and count the active tasks*/
    for (auto it = waitingTaskListCopy.begin();
         it != waitingTaskListCopy.end();
         it++)
    {
        //waiting task are not active so just signal a kill
        (*it)->setKilled();
    }

    for (auto it = taskListCopy.begin();
         it != taskListCopy.end();
         it++)
    {
        Task* task = (*it);
        /*grep the active tasks*/
        if (task->isActive()) leftToKillActiveTaskCounter++;
        
        task->setKilled();
    }

    std::cout << "block" << std::endl;

    /*we wait until all the active task in the lists were destroyed.
      the suspended and waiting threads will be killed automatically in
      the next round*/
    //allSelectedActiveTaskGotKilled.wait(lock);

 }