#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"

#include "SceneYobject.h"
#include "Picture.h"
#include "PictureList.h"
#include "AABBColliderYobject.h"
#include <memory>
#include "Action.h"

/* Note that when accessing attributes you always lock before.
   At the moment there is no good implementation of just only lock one locks.
   therefore allowing user to access different attributes in a row (incremental move)
   evrey user must to lock manually the character before accessing*/
class Character: public SceneYobject
{
    public:
        Character(int id,std::string name,
                  PluginList* pluginList);

        virtual ~Character();

        /*set and get the current status. you should aquire the mutex with
          lock before you access this interface
          The default status is "None"*/
        void setStatus(std::string status);
        std::string getStatus();

        /* if you want to access the character from different threads,
           e.g to change the status you should lock this mutex before
           when you want to acess several properties in a row e.g for a incremental
           move (getPosition,setPosition) you can lock the Character*/
        void lock();
        void unlock();

        /* add a picture with a specifier. 
           the specifier is used for referencing.
           The pictures are used for standing, looking in a directions, ...*/
        void addAnimationPicture(std::string specifier, std::string fileName);

        /*set the current displayed picture.
          if the specifier is in the animationList,
          the index describe a position in the picture array for that animation.
          return true if the specifier was found,
          else false. */
        bool setCurrentAnimationPicture(std::string specifier, int index);

        /*set the current displayed picture. 
          return true if the specifier was found,
          else false. */
        virtual bool setCurrentPicture(std::string specifier);

        /* add a picture with a specifier. 
           the specifier is used for referencing.
           The pictures are used for standing, looking in a directions, ...*/
        
        /* the current displayed picture is set to the given picture*/
        virtual void addPicture(std::string specifier, std::string fileName);

        /*test if a Point collides with the character. 
          can be used for a mouse pointer*/
        bool isPointInCollider(Position point);

        /*test if it collides with other objects*/
        bool collides();

        /*updates the collider and position*/
        void setPosition(Position pos);
        void setPosition(int posX, int posY);
        Position getPosition();


        /*get the size of the current picture*/
        Size getSize();

        /*set the walk collider.*/
        void setCollider(int width,int height, int heightOffset);

        /*set the walk function */
        void setWalkAnimationFkt(void (*walkAnimation) (Position sourcePosition, 
                                                        Position targetPosition, 
                                                        int totalElapsedTicks, 
                                                        int elapsedTicks));

        /*get the walk function*/
        void* getWalkAnimationFkt();

        /* try to enqueue a action. if it will be granted and queue is decided by
           the function decideEnqueueAction.*/
        bool tryEnqueueAction(std::shared_ptr<Action> action);

        /* set the function which decided if a new action is enqueued.
           is called by tryEnqueueAction() and therefore the type of the action 
           which should be enqueued is given..*/
        void setDecideEnqueueActionFunction (bool (*decideEnqueueAction) 
                                                    (std::string actionType));

        /* only signal abort to all actions in the queue. 
           the processes who enqueue this action clean it up also.
           this is the only we have not several calls aborting the same action*/
        void abortCurrentAction();

        /*dequeue the current action*/
        void dequeueAction(std::shared_ptr<Action> action);

        void setRenderPriority(double priority);


        /*deactivate/active the collider for collision checks*/
        void activateCollider();
        void deactivateCollider();

    protected:
        /*the position in the scene*/
        int posX;
        int posY;

        /*picture Map*/
        std::shared_ptr<PictureList> pictureMap;

        /* a string which describe the current status.
           Depending on the logic this could be walking, initwalk, animation etc.
           The default status is "None"*/
        std::string currentStatus;

        /*because several threads can try to access the character, 
          e.g to change the status, we need a lock*/
        std::mutex characterMutex;

        /*the mouse collider of the character*/
        std::shared_ptr<AABBColliderYobject> charCollider;

                /*the collider of the character*/
        std::shared_ptr<AABBColliderYobject> walkCollider;


        /*walk function which is called by the walk to subtask*/
        void (*walkAnimation) (Position sourcePosition, 
                               Position targetPosition, 
                               int totalElapsedTicks, 
                               int elapsedTicks);

        /*save a pointer of the pluginlist*/
        PluginList* pluginList;

        /* a pointer to a granting function for actions.*/
        bool (*decideEnqueueAction) (std::string actionType);

        /* the action queue*/
        std::vector<std::shared_ptr<Action>>* actionQueue;

    private:
};

#endif // PICTURE_H
