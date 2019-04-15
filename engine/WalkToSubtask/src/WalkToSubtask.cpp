#include "WalkToSubtask.h"


WalkToSubtask::WalkToSubtask(PluginList* pluginList,
                             int id,
                             std::string eventName,
                             int characterId,
                             Position targetPosition,
                             double speed,
                             void (*walkAnimation) (Position sourcePosition, 
                                                    Position targetPosition, 
                                                    int totalElapsedTicks, 
                                                    int elapsedTicks)
                            ) : Subtask(id)
{

    this->eventName = eventName;
    this->targetPosition = targetPosition;
    this->speed = speed;

    try
    {
        /*try to assign the global timer */
        this->timer = (GlobalTimer*) pluginList->get(GlobalTimer::getPluginName());
    }
    catch(std::runtime_error& e)
    {
        std::cerr <<"Cant find the global timer, needed for the walkToSubtask\n";
    }

    try
    {
        taskManager = ((TaskManager*) pluginList->get(TaskManager::getPluginName()));
    }
    catch(std::runtime_error& e)
    {    
        std::cerr <<"Cant find the task manager, needed for the walkToSubtask\n";
    }

    if (characterId > -1)
    {
        try
        {
            SceneContainer* scene = (SceneContainer*) pluginList->get(SceneContainer::getPluginName());
            std::shared_ptr<Yobject> charYobject = scene->getYobject(characterId);
            this->character = std::static_pointer_cast<Character>(charYobject);
        }
        catch(std::runtime_error& e)
        {    
            std::cerr << e.what() << std::endl;
        } 
    }

    //check the walk animation fkt
    /*TODO: do we need a lock here?*/    
    if (walkAnimation == nullptr || walkAnimation == NULL)
    {
        //try to get the default walkAnimation from the Character
        walkAnimation =  (void (*) (Position, Position , int , int ))  character->getWalkAnimationFkt();

        if (walkAnimation ==nullptr || walkAnimation == NULL)
            std::cerr <<"No walk animation fkt was given to the walk to subtask\n";

    }

    this->walkAnimation = walkAnimation;

    /*TODO: do we need a lock here?*/    
    sourcePosition = character->getPosition();

    walkAction = std::make_shared<WalkAction>();
}

WalkToSubtask::~WalkToSubtask()
{
    this->character.reset();
    walkAction.reset();
}


/* TODO: add a status flag to the walk function to signal crash or stop etc.*/
/** just fire the next node */
void WalkToSubtask::process()
{

    //std::cerr << walkAction.use_count();

    /* try to start character action*/
    if (!(character->tryEnqueueAction(walkAction)))
        return;

    /* sleep until we can start*/
    while(walkAction->getState() == "Wait")
    {
        taskManager->suspendTaskUntilNextRound(eventName);
    }

    /* if we get canceld here no big deal just dequeue and quit*/
    if (walkAction->getState() == "Aborted")
    {
        character->dequeueAction(walkAction);
        return;
    }

    /* now we can start*/

    double totalElapsedTicks = 0;

    int distanceX = targetPosition.posX - sourcePosition.posX;
    int distanceY = targetPosition.posY - sourcePosition.posY;

    double distance = sqrt( (double)distanceX*distanceX + (double) distanceY*distanceY);

    /*distance/speed = time*/
    double totalTicks = distance/speed * 1000.0f; //1000 for ms

    character->lock();
    character->setStatus("Walk");
    character->unlock();

    while(totalElapsedTicks < totalTicks)
    {
        double elapsedTicks =  timer->getTicksForCurrentFrame();
        totalElapsedTicks += elapsedTicks;

        double lambda = totalElapsedTicks/totalTicks;

        /*linear interpolation*/
        int newPosX = (1.0f-lambda)*(double)sourcePosition.posX + lambda*(double)targetPosition.posX;
        int newPosY = (1.0f-lambda)*(double)sourcePosition.posY + lambda*(double)targetPosition.posY;

        /* we access the character, so we lock him 
           to prevent erros due multitasking*/
        character->lock();

        /* check the status if we got aborted*/
        //TODO: do we need the lock for walkAnim????
        if (walkAction->getState() == "Aborted")
        {
            //signal an end of the walk
            if (walkAnimation != nullptr && walkAnimation != NULL)
                    walkAnimation(sourcePosition,targetPosition,-1,-1);

            /*unlock the mutex and break up;*/
            character->setStatus("None");
            character->unlock();
            character->dequeueAction(walkAction);
            return;
        }

        /*theres no other animation playing. process the walk*/
        character->setPosition(newPosX,newPosY);

        //check if there are collision with the new position
        if (character->collides())
        {   
            //try to solve the collision
            std::cout << "collision on pos:" << newPosX << " " << newPosY << "\n";
            trySolveCollision(totalElapsedTicks, totalTicks, elapsedTicks);
            
            //signal an end of the walk
            if (walkAnimation != nullptr && walkAnimation != NULL)
                walkAnimation(sourcePosition,targetPosition,-1,-1);

            /*unlock the mutex and break up;*/
            character->setStatus("None");
            character->unlock();
            character->dequeueAction(walkAction);
            return;
        }

        /*update the current picture of the character*/
        if (walkAnimation != nullptr && walkAnimation != NULL)
            walkAnimation(sourcePosition,targetPosition,
                          totalElapsedTicks,elapsedTicks);

        /*realease the lock to give another task the chance to edit the char*/
        character->unlock();
        taskManager->suspendTaskUntilNextRound(eventName);

    }

    
    /* to be sure the character is on the end position => set him there*/
    character->lock();
    character->setPosition(targetPosition.posX,targetPosition.posY);

    /*call walkAnimation to signal a the end of the animation*/
    if (walkAnimation != nullptr && walkAnimation != NULL)
        walkAnimation(sourcePosition,targetPosition,-1,-1);

    /* now the walk is over. 
       change the status of the character back to None*/
    character->setStatus("None");
    character->unlock();
    /*finished. dequeue the action*/
    character->dequeueAction(walkAction);

}

/**assume that you have locked the char*/
void WalkToSubtask::trySolveCollision(double totalElapsedTicks, 
                                      double totalTicks, 
                                      double elapsedTicks)
{
    //go back until it doesn't collide
    double ticks = totalElapsedTicks;
    double epsilon = 10.0f;

    double newPosX = 0.0f;
    double newPosY = 0.0f;

    double lambda = 0.0f;
    int loopCounter = 0;   
    do
    {
        /*try to solve the collision*/

        /* not place him exactly there where he started in the last frame*/
        ticks -= (elapsedTicks + epsilon);

        lambda = ticks/totalTicks;

        /* have traveled back to far. set him on the start position
            there should be no collision*/
        if ((lambda < 0) || loopCounter >= 10) lambda = 0;

        /*linear interpolation*/
        newPosX = (1.0f-lambda)*(double)sourcePosition.posX + lambda*(double)targetPosition.posX;
        newPosY = (1.0f-lambda)*(double)sourcePosition.posY + lambda*(double)targetPosition.posY;

        //update the characters position and check for collisions
        character->setPosition(newPosX,newPosY);

        //to prevent endless loops
        loopCounter++;

    } while((character->collides()) && (loopCounter <= 10) );

}