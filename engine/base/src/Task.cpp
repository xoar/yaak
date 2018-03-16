#include "Task.h"

Task::Task(TaskManager *taskManager,std::string name,void (*run) ())
{
    this->taskManager = taskManager;
    this->status = WAITING;
    this->name=name;
    this->run = run;
    this->killed = false;
}

std::string Task::getName()
{
    return this->name;
}

void Task::setName(std::string name)
{
    this->name=name;
}

void Task::setWaiting()
{
    this->status = WAITING;
}

void Task::setActive()
{
    this->status = ACTIVE;
}

void Task::setSuspended()
{
    this->status = SUSPENDED;
}


bool Task::isWaiting()
{
    return (this->status == WAITING);
}

bool Task::isActive()
{
    return (this->status == ACTIVE);
}

bool  Task::isSuspended()
{
    return (this->status == SUSPENDED);
}


TaskManager * Task::getTaskManager()
{
    return this->taskManager;
}


void Task::setKilled()
{
    killed = true;
}

bool Task::gotKilled()
{
    return killed;
}