#include "Subtask.h"

Subtask::Subtask(int id)
{
    this->id = id;
}

int Subtask::getId()
{
    return id;
}

void Subtask::setId(int id)
{
    this->id = id;
}
