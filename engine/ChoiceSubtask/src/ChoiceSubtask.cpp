#include "ChoiceSubtask.h"

int ChoiceTryToLockCharacter(int id, 
                              const char* eventName, 
                              int (*clearTaskCollision)(),
                              void * pluginList )
{

    /* check if therer are collisions with the walk*/
    
    CharacterLock(pluginList,id);

    /*wait until the started walk or another animation is over*/
    while (!clearTaskCollision())
    {
        //havn't the permission to start. wait
        CharacterUnlock(pluginList,id);

        if(!SuspendTaskUntilNextRound(pluginList,eventName))
        {
            /**recieved kill signal. signal it*/
            return 0;
        }
        /* get the lock again to evaluate the collision*/
        CharacterLock(pluginList,id);
    }

    //no collisions set the status to Choice
    CharacterSetStatus(pluginList,id,eventName);

    //all things are done, release the lock
    CharacterUnlock(pluginList,id);

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