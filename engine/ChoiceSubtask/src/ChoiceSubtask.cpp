#include "ChoiceSubtask.h"

#include "TaskManager.h"
#include "Character.h"
#include "Action.h"
#include <iostream>
#include <string>

class ChoiceAction : public Action
{
    public: 
        ChoiceAction() : Action("Choice") {}
};

int ChoiceTryToLockCharacter(int characterId, 
                              const char* eventName,
                              void * pluginList )
{

    PluginList* _pluginList = (PluginList*) pluginList; 
    TaskManager* taskManager;

    try
    {
        taskManager = ((TaskManager*) _pluginList->get(TaskManager::getPluginName()));
    }
    catch(std::runtime_error& e)
    {    
        std::cerr <<"Cant find the task manager, needed for the walkToSubtask\n";
    }

    std::shared_ptr<Action> choiceAction = std::make_shared<ChoiceAction>();

    std::shared_ptr<Character> character = nullptr;

    if (characterId > -1)
    {
        try
        {
            SceneContainer* scene = ((SceneContainer*) _pluginList->get(SceneContainer::getPluginName()));
            std::shared_ptr<Yobject> charYobject = scene->getYobject(characterId);
            character = std::static_pointer_cast<Character>(charYobject);
        }
        catch(std::runtime_error& e)
        {    
            std::cerr << e.what() << std::endl;
        } 
    }

    /* try to enqueue the action*/
    if (!(character->tryEnqueueAction(choiceAction)))
        return 0;

    /* sleep until we can start*/
    try
    {
        while(choiceAction->getState() == "Wait")
        {
            taskManager->suspendTaskUntilNextRound(eventName);
        }
    }
    catch (KillException& e)
    {
        return 0;
    }

    character->lock();
    /* if we get canceld here no big deal just dequeue and quit*/
    if (choiceAction->getState() == "Aborted")
    {
        character->dequeueAction(choiceAction);
        character->unlock();
        return 0;
    }

    //no collisions set the status to Choice
    character->setStatus(std::string(eventName));

    character->unlock();
    /** all things were done successfully*/
    return 1;
}


void ChoiceBuildMessage(int * currentPosX, 
                        int* currentPosY,
                        MessageYobjectStructPtr* message,
                        TriggerZoneStructPtr* zone,
                        const char * zoneName,
                        const char * text,
                        int subtaskId,
                        void * pluginList
                        )
{

    int width;
    int height;

    /*build the message*/
    *message = MessageYobjectConstructor(0,
                                         subtaskId,
                                         text,
                                         -1,
                                         pluginList
                                         );
    
    /*set the position*/
    MessageYobjectSetPosition2I(*message,*currentPosX,*currentPosY);
    /*set a yellow default color*/
    Color defaultColor = { 255,144,0 };
    MessageYobjectSetColor(*message,defaultColor);

    /*create the texture to get the correct size*/
    MessageYobjectSignalInitRessources(*message);

    MessageYobjectGetSize(*message,&width,&height);


    *zone =  TriggerZoneConstructor(0,zoneName,pluginList);
    TriggerZoneSetRectangle4I(*zone,*currentPosX,*currentPosY,width,height);

    *currentPosY= *currentPosY - height - 2; // 2 for a bit space between the text fields
    if (*currentPosY < 0) *currentPosY = 0; // TODO:should throw an error
}

void ChoiceFinish(void * pluginList,int characterId)
{

    PluginList* _pluginList = (PluginList*) pluginList; 
    std::shared_ptr<Character> character = nullptr;

    if (characterId > -1)
    {
        try
        {
            SceneContainer* scene = (SceneContainer*) _pluginList->get(SceneContainer::getPluginName());
            std::shared_ptr<Yobject> charYobject = scene->getYobject(characterId);
            character = std::static_pointer_cast<Character>(charYobject);
        }
        catch(std::runtime_error& e)
        {    
            std::cerr << e.what() << std::endl;
        } 
    }

    character->lock();
    character->dequeueAction(nullptr);
    character->unlock();

}