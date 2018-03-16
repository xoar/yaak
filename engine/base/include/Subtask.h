#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include "Utils.h"
#include <PluginList.h>

class Subtask
{
    public:

    Subtask(int id);

    /** this is the process function which must be overriden to implement the disired functionality *
     *  this function can be only called once per game loop
     */
    virtual void process() {};

    /** get its id. */
    int getId();
    /** set its id */
    void setId(int id);

    protected:
    /** its id to find it in the availible Subtask List */
    int id;
};

#endif // NODE_H_INCLUDED
