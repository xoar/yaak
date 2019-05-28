#include "Character.h"
#include "ColliderPlugin.h"

bool grantAll(std::string actionType) {return true;}


Character::Character(int id,
                     std::string name,
                     PluginList* pluginList)
                     : SceneYobject(id,name,pluginList)
{
    pictureMap = std::make_shared<PictureList>(0,id,pluginList);
    pictureMap->registerYobject(pictureMap);
    /*create the collider for the character*/
    charCollider = std::make_shared<AABBColliderYobject>(0,id,pluginList);
    charCollider->registerYobject(charCollider);


    charCollider->setPictureList(pictureMap);

    //the walk collider is only use if the user set one
    walkCollider = nullptr;

    walkAnimation = nullptr;

    currentStatus = "None";

    this->pluginList = pluginList;

    decideEnqueueAction = grantAll;

    actionQueue = new std::vector<std::shared_ptr<Action>>();

    posX = 0;
    posY = 0;

    /*attach the collider to us*/
    this->attachChild(std::static_pointer_cast<SceneYobject>(charCollider));

    charCollider->setTag("PictureCollider");

}


Size Character::getSize()
{
    lock();

    Size result = pictureMap->getSize();
    
    unlock();

    return result;
}

bool Character::isPointInCollider(Position point)
{
    lock();

    bool result = charCollider->isPointInCollider(point);

    unlock();

    return result;
}

bool Character::WalkColliderCollides(std::string type,std::string tag)

{
    lock();

    bool result = false;

    if (walkCollider)
    {
        //std::cout << "\n!!!!check walk collider\n";
        result =  walkCollider->collides(type,tag);
    }

    unlock();

    return result;
    
}

bool Character::CurrentPictureCollides(std::string type,std::string tag)
{
    lock();

    bool result =  charCollider->collides(type,tag);

    unlock();

    return result;
    
}


bool Character::setCurrentPicture(std::string specifier)
{
    return Character::setCurrentAnimationPicture(specifier,0);
}

void Character::addPicture(std::string specifier, std::string fileName)
{

    lock();

    /*TODO: check if there is already a specifier in the list*/
    /* first add+set the new picture*/
    pictureMap->addPicture(specifier,fileName);

    /*now set the current piucture and update the collider*/
    setCurrentPicture(specifier);

    unlock();
}


void Character::setPosition(Position pos)
{
    this->setPosition(pos.posX, pos.posY);
}

Position Character::getPosition()
{
    lock();

    Position pos;
    pos.posX = posX;
    pos.posY = posY;

    unlock();

    return pos;
}

void Character::setPosition(int posX, int posY)
{
    lock();

    /*propagate the movement*/
    int dx = posX - this->posX;
    int dy = posY - this->posY;

    translateChilds(dx, dy);

    /*updated our position*/
    this->posX = posX;
    this->posY = posY;
    
    /*update the images*/
    pictureMap->setPosition(posX,posY);

    unlock();
}


bool Character::setCurrentAnimationPicture(std::string specifier, int index)
{
    lock();

    /* first set the new picture*/
    /* picture are insert alone, in contrast to animations*/
    bool status = pictureMap->setCurrentPicture(specifier,index);

    /*change the collider. for clicking with the mouse while having an animation*/
    if (status){
        //get the current size
        Size size = this->getSize();
        if (size.width != -1) charCollider->setSize(size.width,size.height);
    }

    unlock();

    return status;
}


void Character::addAnimationPicture(std::string specifier, std::string fileName)
{
    lock();

    /* first add+set the new picture*/
    pictureMap->addPicture(specifier,fileName);
    
    /*no update of the current picture and collider for animations*/

    unlock();
}


Character::~Character()
{
    lock();

    //destroy the collider
    charCollider->unregisterYobject(charCollider);
    charCollider.reset();

    if (walkCollider)
    {
    	walkCollider->unregisterYobject(charCollider);
    	walkCollider.reset();
    }
    
    pictureMap->unregisterYobject(pictureMap);
    pictureMap.reset();

    actionQueue->clear();
    delete actionQueue;

    

    unlock();
}


void Character::lock()
{ 
    characterMutex.lock(); 
}

void Character::unlock() 
{ 
    characterMutex.unlock(); 
}

void Character::setStatus(std::string status)
{
    lock();

    currentStatus = status;

    unlock();
}
std::string Character::getStatus()
{
    return currentStatus;
}

void Character::setWalkCollider(int width,int height,int heightOffset)
{
    lock();

    //the walk collider is used. create & register it.
    walkCollider = std::make_shared<AABBColliderYobject>(1,id,pluginList);
    walkCollider->registerYobject(walkCollider);

    //the the size of the walk collider
    walkCollider->setSize(width,height);

    /* set the walk collider. use a fix maximum to prevent bobing*/
    walkCollider->setPosition(posX,posY+heightOffset);

    walkCollider->setTag("WalkCollider");

    /*register the walkCollider to the Character*/
    this->attachChild(std::static_pointer_cast<SceneYobject>(walkCollider));

    unlock();

}

/*set the walk function */
void Character::setWalkAnimationFkt(void (*walkAnimation) (Position sourcePosition, 
                                                Position targetPosition, 
                                                int totalElapsedTicks, 
                                                int elapsedTicks))
{
    lock();

    this->walkAnimation = walkAnimation;

    unlock();
}

/*set the walk function */
void* Character::getWalkAnimationFkt()
{
    return (void*) this->walkAnimation;
}

/* try to enqueue a action. if it will be granted and queue is decided by
   the function decideEnqueueAction.*/
bool Character::tryEnqueueAction(std::shared_ptr<Action> action)
{
   
    if(!action)
    {
        std::cerr << "invalid pointer";
        return false;
    }

    /*/* Now check if the action is granted*/
    bool isGranted = (*decideEnqueueAction)(action->getType());

    /* get the mutex to avoid the queue get fucked up*/
    lock();

    // when it was granted it can be add to the queue for later execution
    if (isGranted)
        actionQueue->push_back(action);

    if (actionQueue->size() == 1)
        action->setState("Ready");

    unlock();

    return true;
}

/* set the function which decided if a new action is enqueued.
   is called by tryEnqueueAction() and therefore the type of the action 
   which should be enqueued is given.*/
void Character::setDecideEnqueueActionFunction (bool (*decideEnqueueAction) 
                                                       (std::string actionType))
{
    lock();

    this->decideEnqueueAction = decideEnqueueAction;

    unlock();
}


void Character::dequeueAction(std::shared_ptr<Action> action)
{

    lock();

    if (!actionQueue->empty())
    {

        if (action == actionQueue->front())
        {
            /*dequeue it*/
            actionQueue->erase(actionQueue->begin());

            //set the next ready
            if (actionQueue->size() >= 1)
               (actionQueue->front())->setState("Ready");
        }
        else
            std::cerr << "not allowed to dequeue element";
    }

    unlock();
}

/*only signal abort to all actions in the queue. 
  the processes who enqueue this action clean it up also.
  this is the only we have not several calls aborting the same action*/
void Character::abortCurrentAction()
{
    lock();

    /* signal abort to all actions*/
    /* This is simple because only one action should be waiting the rest should aborting
       or wait to abort*/
    for (auto action : *actionQueue) 
    {
        action->signalAbort();
    }

    unlock();

}

void Character::setRenderPriority(double priority)
{

    lock();

    pictureMap->setRenderPriority(priority);

    unlock();
}

void Character::activateCollider()
{
    lock();

    charCollider->setActive();

    unlock();
}

void Character::deactivateCollider()
{
    lock();

    charCollider->setInactive();

    unlock();
}