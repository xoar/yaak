#include "string.h"

#include "TestPlugin.h"
#include "PluginUtils.h"


Color defaultColor = { 0, 0, 0 };
const char * defaultFont = "../res/SourceSansPro-Regular.ttf";

Position defaultPos = {10,20 };
int defaultSize = 30;
double defaultTime = 10.5;


int Yoda = 0;
int Obi = 0;


void YodaLuke();
void ObiLuke();
void InitScene();
void WalkEvent();
void DisplayYodasName();
void YodaMessage();
void Choice();

void pluginInit (void* _pluginList,void *_renderer)
{

    buildRefs(_pluginList,_renderer);

    AddTaskForNextRound(pluginList,"InitScene", &InitScene);

}



void walkAnimation(Position sourcePosition, 
                   Position targetPosition,
                   int totalElapsedTicks,
                   int elapsedTicks)
{
    /*calc the index for the animation list. %5 because there are 6 images.
      the speed is reduced by dividing 100 */
    int index = totalElapsedTicks/100 % 5;

    /* now check in which direction the character walk.
       than set the right animation picture for walking to south, noth, etc.*/
    int directionInDegree = getDirection(sourcePosition,targetPosition);

    /*from north east to south east. right walk animation*/
    if (((0 <= directionInDegree) && (directionInDegree <= 45)) || 
        ((315 <= directionInDegree) && (directionInDegree <= 360)))
    {
        CharacterSetCurrentPictureById(pluginList,2,"walking right",index);
    }
    /* upper direction*/
    else if ((45 <= directionInDegree) && (directionInDegree <= 135))
    {
        CharacterSetCurrentPictureById(pluginList,2,"walking up",index);
    }
    /*left direction*/
    else if ((135 <= directionInDegree) && (directionInDegree <= 225))
    {
        CharacterSetCurrentPictureById(pluginList,2,"walking left",index);
    }
    /*down*/
    else if ((225 <= directionInDegree) && (directionInDegree <= 315))
    {
        CharacterSetCurrentPictureById(pluginList,2,"walking down",index);
    }
}

/*check if there are collisions when the task start which has to
  be solved. if it returns true all things are solved and we can continue. 
  otherwise we cancel the task start
  the character lock should be aquired when this function is called*/ 
int clearTaskCollision()
{

    const char* status =  CharacterGetStatus(pluginList,2);

    if ( (strcmp(status,"InitWalk") == 0) || (strcmp(status,"None") == 0))
    {
        /*in the init phase of the walk there is no update of the picture.
          so there is nothing to resolve. the status is changed by the caller*/
        return 1;
    }

    //an animation or somthing else is processing.
    return 0;
}

void Choice()
{

    /* try to set the status of the character to "choice".
       block until the set*/
    ChoiceTryToLockCharacter(2,"Choice",&clearTaskCollision,pluginList);


    /** --------------choice ------------------------*/
    Color defaultColor = { 255,144,0 };

    MessageYobjectStructPtr yodaMessage;
    TriggerZoneStructPtr yodaMessageZone;

    MessageYobjectStructPtr obiMessage;
    TriggerZoneStructPtr obiMessageZone;


    int currentPosX = 380;
    int currentPosY = 700;

    /* --------  build section: choose which message to display ---------------*/ 

    if (!Yoda)
    {
        ChoiceBuildMessage(&currentPosX,
                           &currentPosY,
                           &yodaMessage,
                           &yodaMessageZone,
                           "yodaMessageZone",
                           "hey Yoda there",
                           defaultFont,
                           defaultSize,
                           defaultColor,
                           18,
                           pluginList,
                           renderer);
    }

    if (!Obi)
    {
        ChoiceBuildMessage(&currentPosX,
                           &currentPosY,
                           &obiMessage,
                           &obiMessageZone,
                           "obiMessageZone",
                           "hey Obi there",
                           defaultFont,
                           defaultSize,
                           defaultColor,
                           18,
                           pluginList,
                           renderer);
    }

    /* -------  test section: check if the user click on one of the messages --*/
    int loop = 1;

    while(loop)
    {

        WaitOnInputStructPtr sub20 = WaitOnInputConstructor(pluginList, 20,"Choice","mouse","left");
        WaitOnInputProcess(sub20);

        GameEvents events = EventSystemGetCurrentEvents(pluginList);
        Position targetPosition = {events.mouseX,events.mouseY};

        if (!Yoda)
        {
            if (IsPointInTriggerZone(yodaMessageZone,targetPosition))
            {
                 AddAndRunTask(pluginList,"YodaMessage", &YodaMessage);
                 loop = 0;
            }
        }

        if (!Obi)
        {
            if (IsPointInTriggerZone(obiMessageZone,targetPosition))
            {
                 printf("\nHey you obi wan !\n");
                 loop = 0;
            }
        }

        //if we just repeat the loop with out that WaitOn just
        //dont block if the mouse was clicked -> endless loop
        if (loop) SuspendTaskUntilNextRound(pluginList,"Choice");

    }

    if (yodaMessage) MessageYobjectDestructor(yodaMessage);
    if (obiMessage) MessageYobjectDestructor(obiMessage);


    /** --------------end choice ------------------------*/
    
    CharacterLock(pluginList,2);
    CharacterSetStatus(pluginList,2,"None");
    CharacterUnlock(pluginList,2);

    RemoveTask(pluginList,"Choice");
}

void YodaMessage()
{
    printf( "\n hey yoda there!!!\n ");
    RemoveTask(pluginList,"YodaMessage");
}


void InitScene()
{

    CharacterStructPtr char0 = CharacterConstructor(0,  "Desert",pluginList,renderer);
    CharacterAddPicture(char0,"standing","../res/purpurRoom.gif");
    CharacterSetPosition2I(char0,0,0);

    CharacterStructPtr char1 = CharacterConstructor(1,  "Yoda",pluginList,renderer);
    CharacterAddPicture(char1,"standing","../res/yoda.gif");


    CharacterSetPosition2I(char1,70,480);

    CharacterStructPtr char2 = CharacterConstructor(2,  "Luke",pluginList,renderer);
    CharacterAddPicture(char2,"standing","../res/Stand2.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR1.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR2.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR3.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR4.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR5.png");
    CharacterAddAnimationPicture(char2,"walking right","../res/WR6.png");

    CharacterAddAnimationPicture(char2,"walking left","../res/WL1.png");
    CharacterAddAnimationPicture(char2,"walking left","../res/WL2.png");
    CharacterAddAnimationPicture(char2,"walking left","../res/WL3.png");
    CharacterAddAnimationPicture(char2,"walking left","../res/WL4.png");
    CharacterAddAnimationPicture(char2,"walking left","../res/WL5.png");
    CharacterAddAnimationPicture(char2,"walking left","../res/WL6.png");

    CharacterAddAnimationPicture(char2,"walking up","../res/WU0.png");
    CharacterAddAnimationPicture(char2,"walking up","../res/WU1.png");
    CharacterAddAnimationPicture(char2,"walking up","../res/WU2.png");
    CharacterAddAnimationPicture(char2,"walking up","../res/WU3.png");
    CharacterAddAnimationPicture(char2,"walking up","../res/WU4.png");
    CharacterAddAnimationPicture(char2,"walking up","../res/WU5.png");

    CharacterAddAnimationPicture(char2,"walking down","../res/WD0.png");
    CharacterAddAnimationPicture(char2,"walking down","../res/WD1.png");
    CharacterAddAnimationPicture(char2,"walking down","../res/WD2.png");
    CharacterAddAnimationPicture(char2,"walking down","../res/WD3.png");
    CharacterAddAnimationPicture(char2,"walking down","../res/WD4.png");
    CharacterAddAnimationPicture(char2,"walking down","../res/WD5.png");


    CharacterSetPosition2I(char2,300,300);

    CharacterStructPtr char3 = CharacterConstructor(3,  "ObiWan",pluginList,renderer);
    CharacterAddPicture(char3,"standing","../res/obi.gif");
    CharacterSetPosition2I(char3,500,300);

    AddAndRunTask(pluginList,"YodaLuke", &YodaLuke);

    RemoveTask(pluginList,"InitScene");

}

void YodaLuke(){

    MessageStructPtr subtask0 = MessageConstructor(
                                 pluginList, 
                                 0, 
                                 "*A long time ago, in a galaxy far, far away....*",
                                 -1, 
                                 defaultTime,
                                 defaultFont,
                                 defaultPos,
                                 defaultSize,
                                 defaultColor,
                                 "YodaLuke" ,
                                 renderer);

    MessageSetTime(subtask0,4.0);
    MessageSetFontSize(subtask0,50);
    MessageSetColor3I(subtask0,255,144,0);
    MessageProcess(subtask0);


    TriggerStructPtr subtask3 = TriggerConstructor(pluginList, 3);
    TriggerAddSubtask(subtask3,"ObiLuke", &ObiLuke );
    TriggerAddSubtask(subtask3,"WalkEvent", &WalkEvent );
    TriggerAddSubtask(subtask3,"DisplayYodasName", &DisplayYodasName );
    TriggerAddSubtask(subtask3,"Choice", &Choice );

    TriggerProcess(subtask3);

    RemoveTask(pluginList,"YodaLuke");

}

void ObiLuke(){
    printf("obi and luke say somethig\n");

    RemoveTask(pluginList,"ObiLuke");
}


void DisplayYodasName()
{
    TriggerZoneStructPtr zone1 =  TriggerZoneConstructor(4, "zone1",pluginList);
    TriggerZoneSetRectangle4I(zone1,70,480,120,120);

    while(1)
    {
        GameEvents events = EventSystemGetCurrentEvents(pluginList);
        Position targetPosition = {events.mouseX,events.mouseY};

        if (IsPointInTriggerZone(zone1,targetPosition))
        {

            MessageStructPtr subtask0 = MessageConstructor(
                                 pluginList, 
                                 0, 
                                 "Yoda",
                                 -1, 
                                 defaultTime,
                                 defaultFont,
                                 defaultPos,
                                 defaultSize,
                                 defaultColor,
                                 "DisplayYodasName" ,
                                 renderer);

            //0 time means one frame//
            MessageSetTime(subtask0,0);
            MessageSetFontSize(subtask0,20);
            MessageSetColor3I(subtask0,255,144,0);
            MessageProcess(subtask0);
        }
        else SuspendTaskUntilNextRound(pluginList,"DisplayYodasName");


    }
    

}


void WalkEvent(){

    WaitOnInputStructPtr sub15 = WaitOnInputConstructor(pluginList, 
                                                        15,
                                                        "WalkEvent",
                                                        "mouse","left");
    WaitOnInputProcess(sub15);

    GameEvents events = EventSystemGetCurrentEvents(pluginList);

    /*get the size of the current picture to point 
      on the shoes with the mouspointer. 
      Hint: ccordinates are growing up from the left upper corner*/

    Rectangle size = CharacterGetSizeById(pluginList,2);
    int LukeWidth = size.width;
    int LukeHeight = size.height;


    Position targetPosition = {(events.mouseX - LukeWidth),
                               (events.mouseY - LukeHeight)};

    WalkToStructPtr sub16 = WalkToConstructor(pluginList, 
                                              16,
                                              "WalkEvent",
                                              2,
                                              targetPosition, 
                                              100,
                                              walkAnimation);
    WalkToProcess(sub16);

    TriggerStructPtr subtask14 = TriggerConstructor(pluginList, 14);
    TriggerAddSubtask(subtask14,"WalkEvent", &WalkEvent );
    TriggerProcess(subtask14);

    RemoveTask(pluginList,"WalkEvent");

}