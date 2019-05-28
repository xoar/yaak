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

/* Note that when accessing attributes in a row you always lock before.*/
class Character: public SceneYobject
{
    public:
        Character(int id,std::string name,
                  PluginList* pluginList);

        virtual ~Character();


//----------------------- Position ---------------------------------------------

        /*updates the relative position and moves the collider*/
        void setPosition(Position pos);
        void setPosition(int posX, int posY);

        /*get the current relative position (see: realtive ccordinate)*/
        Position getPosition();


//-----------------------Picture -----------------------------------------------

        /* add a picture with a specifier. 
           the specifier is used for referencing.
           The pictures are used for standing, looking in a directions, ...*/
        
        /* the current displayed picture is set to the given picture*/
        virtual void addPicture(std::string specifier, std::string fileName);

        /*set the current displayed picture. 
          return true if the specifier was found,
          else false. */
        virtual bool setCurrentPicture(std::string specifier);


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


//-----------------------Mutex access ------------------------------------------
        
        /* if you want to access the character from different threads and 
           you want to acess several properties in a row e.g for a incremental
           move (getPosition,setPosition) you can lock the Character*/
        void lock();
        void unlock();

//----------------------- Status ----------------------------------------------- 

        /*set and get the current status.
          The default status is "None"*/
        void setStatus(std::string status);
        std::string getStatus();

//----------------------- Collider Interface------------------------------------

        /*test if a Point collides with the character. 
          can be used for a mouse pointer*/
        bool isPointInCollider(Position point);

        /*test if the walk collider collides with other objects
          You can specify the type: AABB, Segment
          and the tag: WalkCollider, PictureCollider*/
        bool WalkColliderCollides(std::string type,std::string tag);

        bool CurrentPictureCollides(std::string type,std::string tag);

        /*set the walk collider.*/
        void setWalkCollider(int width,int height, int heightOffset);

        /*deactivate/active the collider for collision checks*/
        void activateCollider();
        void deactivateCollider();


//------------------------ Action Interface ------------------------------------

        /* try to enqueue a action. if it will be granted and queue is decided by
           the function decideEnqueueAction.*/
        bool tryEnqueueAction(std::shared_ptr<Action> action);

        /* set the function which decided if a new action is enqueued.
           is called by tryEnqueueAction() and therefore the type of the action 
           which should be enqueued is given..*/
        void setDecideEnqueueActionFunction (int (*decideEnqueueAction) 
                                                    (char* actionType));

        /* only signal abort to all actions in the queue. 
           The processes who enqueue its action also clean it up itself.
           This prevent us from the case that several calls aborting the same action*/
        void abortCurrentActions();

        /*try to dequeue the first action in the queue.Checks if it is euqal to the given action.
          should only be used by the task who enqueued this action and 
          got signaled an abort or finished for its job*/
        /* if action is nullptr it dequeue the first element without a check*/
        void dequeueAction(std::shared_ptr<Action> action);


//------------------------ Walk Animation --------------------------------------


        /*set the walk function */
        void setWalkAnimationFkt(void (*walkAnimation) (Position sourcePosition, 
                                                        Position targetPosition, 
                                                        int totalElapsedTicks, 
                                                        int elapsedTicks));

        /*get the walk function*/
        void* getWalkAnimationFkt();


//------------------------ Other -----------------------------------------------

        /*get the size of the current picture*/
        Size getSize();

        void setRenderPriority(double priority);


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
        std::recursive_mutex characterMutex;

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
        int (*decideEnqueueAction) (char* actionType);

        /* the action queue*/
        std::vector<std::shared_ptr<Action>>* actionQueue;

    private:
};

#endif // PICTURE_H
