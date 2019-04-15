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

    //the walk collider is only use if the user set one
    walkCollider = nullptr;

    walkAnimation = nullptr;

    currentStatus = "None";

    this->pluginList = pluginList;

    maxSizeY = 0;

    decideEnqueueAction = grantAll;

    actionQueue = new std::vector<std::shared_ptr<Action>>();

    posX = 0;
    posY = 0;
}


Size Character::getSize()
{
    return pictureMap->getSize();
}

void Character::updateCollider()
{

    //get the current size
    Size size = this->getSize();
    if (size.width != -1) charCollider->setSize(size.width,size.height);

    //update the position
    charCollider->setPosition(posX,posY);
  
    /* set the walk collider. use a fix maximum to prevent bobing*/
    if (walkCollider)
        walkCollider->setPosition(posX,posY+maxSizeY);
}

bool Character::isPointInCollider(Position point)
{
    return charCollider->isPointInCollider(point);
}

bool Character::collides()
{
    if (walkCollider)
        return walkCollider->collides();
    else 
        return false;
}

bool Character::setCurrentPicture(std::string specifier)
{
    /* first set the new picture*/
    /* picture are insert alone, in contrast to animations*/
    bool status = pictureMap->setCurrentPicture(specifier,0);

    /*now update the collider pos+size*/
    if (status) updateCollider();

    return status;
}

void Character::addPicture(std::string specifier, std::string fileName)
{

    /*TODO: check if there is already a specifier in the list*/
    /* first add+set the new picture*/
    pictureMap->addPicture(specifier,fileName);

    /* update the maxSize*/
    Size size = this->getSize();
    if (size.height > maxSizeY) maxSizeY = size.height;

    /*now set the current piucture and update the collider*/
    setCurrentPicture(specifier);
}


void Character::setPosition(Position pos)
{
    this->setPosition(pos.posX, pos.posY);
}

Position Character::getPosition()
{
    Position pos;
    pos.posX = posX;
    pos.posY = posY;

    return pos;
}

void Character::setPosition(int posX, int posY)
{
    /*updated position + the collider*/
    this->posX = posX;
    this->posY = posY;
    
    //update the position
    updateCollider();

    pictureMap->setPosition(posX,posY);
}


bool Character::setCurrentAnimationPicture(std::string specifier, int index)
{
    /* first set the new picture*/
    /* picture are insert alone, in contrast to animations*/
    bool status = pictureMap->setCurrentPicture(specifier,index);

    /*TODO: collider changes with animation size. change this*/
    if (status) updateCollider();

    return status;
}


void Character::addAnimationPicture(std::string specifier, std::string fileName)
{
    /* first add+set the new picture*/
    pictureMap->addPicture(specifier,fileName);

    /* update the maxSize*/
    Size size = this->getSize();
    if (size.height > maxSizeY) maxSizeY = size.height;
    /*no update of the current picture and collider for animations*/
}


Character::~Character()
{
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
    currentStatus = status;
}
std::string Character::getStatus()
{
    return currentStatus;
}

void Character::setCollider(int width,int height)
{
    //the walk collider is used. create & register it.
    walkCollider = std::make_shared<AABBColliderYobject>(1,id,pluginList);
    walkCollider->registerYobject(walkCollider);

    //the the size of the walk collider
    walkCollider->setSize(width,height);

    //we call updateCollider because for fix collider
    //the position is changed a bit
    updateCollider();

}

/*set the walk function */
void Character::setWalkAnimationFkt(void (*walkAnimation) (Position sourcePosition, 
                                                Position targetPosition, 
                                                int totalElapsedTicks, 
                                                int elapsedTicks))
{
    this->walkAnimation = walkAnimation;
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