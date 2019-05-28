#ifndef WALKEVENT_H
#define WALKEVENT_H

#include "PluginUtils.h"
#include "TestPlugin.h"
#include "stdlib.h" /*free*/ 


void walkAnimation(Position sourcePosition, 
                   Position targetPosition,
                   int totalElapsedTicks,
                   int elapsedTicks)
{
    /*calc the index for the animation list. %4 because there are 4 images.
      the speed is reduced by dividing 100 */
    int animIndex = totalElapsedTicks/150 % 4;

    /* now check in which direction the character walk.
       than set the right animation picture for walking to south, noth, etc.*/

    /*TODO: rename in angle and getAngle*/
    int directionInDegree = getDirection(sourcePosition,targetPosition);

    /*from north east to south east. right walk animation*/
    if (((0 <= directionInDegree) && (directionInDegree <= 45)) || 
        ((315 <= directionInDegree) && (directionInDegree <= 360)))
    {
        /* -1 signal a end of the animation*/
        if (totalElapsedTicks != -1)
            Bernard set current animation picture to "walking right" with index animIndex
        else
            Bernard set current picture to "standing right"
    }
    /* upper direction*/
    else if ((45 <= directionInDegree) && (directionInDegree <= 135))
    {
        /* -1 signal a end of the animation*/
        if (totalElapsedTicks != -1)
            Bernard set current animation picture to "walking up" with index animIndex
        else
            Bernard set current picture to "standing right"

    }
    /*left direction*/
    else if ((135 <= directionInDegree) && (directionInDegree <= 225))
    {
        /* -1 signal a end of the animation*/
        if (totalElapsedTicks != -1)
            Bernard set current animation picture to "walking left" with index animIndex
        else
            Bernard set current picture to "standing left"

    }
    /*down*/
    else if ((225 <= directionInDegree) && (directionInDegree <= 315))
    {
        /* -1 signal a end of the animation*/
        if (totalElapsedTicks != -1)
            Bernard set current animation picture to "walking down" with index animIndex
        else
            Bernard set current picture to "standing right"

    }
}

Event WalkEvent
{

    /*only walk when you click on the left mouse*/
    wait on left mouse click

    /*get the size of the current picture to point 
      on the shoes with the mousepointer. 
      Hint: coordinates are growing up from the left upper corner*/

    /* the id of the main character*/
    int CharacterId = CharacterGetId(pluginList,"Bernard");

    Size psize = CharacterGetSizeById(pluginList,CharacterId);
    int BernardWidth = psize.width;
    int BernardHeight = psize.height;

    GameEvents events = EventSystemGetCurrentEvents(pluginList);

    int posX = events.mouseX - BernardWidth;
    int posY = events.mouseY - BernardHeight;

    /* now walkt to the traget position*/
    Bernard walk to posX,posY

    trigger WalkEvent

}


#endif