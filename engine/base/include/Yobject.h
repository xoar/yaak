#ifndef YOBJECT_H
#define YOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"

class Yobject
{
    public:
        /* A subtask can have several Yobjects, so they don't have a ID but a parent ID.
           Entities:named yobjects have an id through construction by the scene.
           The Entity id and subtask id can be the same occasionally, 
           so we use parentId to differ:
           id 0 subtask yobject, id >0 entity yobject

           TODO: do wee need parentId? even if a subtask have several yobjects,
           a subtask have always the pointers so he can remove the yobject trough the adresses
           from the yobject container*/

        Yobject(int id, int parentId);
        virtual ~Yobject() {};

        /** get its id. */
        int getId();
        /** set its id */
        void setId(int id);
        /** get its id. */
        int getParentId();
        /** set its id */
        void setParentId(int parentId);

        /**set the object type. used as a leightwight rtti approach*/
        void setType(std::string type);
        /**set the object type. used as a leightwight rtti approach*/
        std::string getType();

        /* if the yobjects are entites you can access there name*/
        virtual std::string getName(){return "";}

    protected:

        int id;
        int parentId;

        /*leightwight rtti*/
        std::string type;
};

#endif // YOBJECT_H
