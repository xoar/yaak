#ifndef MESSAGESUBTASK_H
#define MESSAGESUBTASK_H

#include "Position.h"
#include "Color.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct MessageSubtaskStruct ;

typedef struct MessageSubtaskStruct * MessageSubtaskStructPtr;

/* the Constructor*/
MessageSubtaskStructPtr MessageSubtaskConstructor(void* pluginList,
			                                    int id,
			                                    const char* text,
			                                    int characterId,
			                                    const char* eventName);

/** this is the process function which must be overriden
    to implement the disired functionality */

int MessageSubtaskProcess(MessageSubtaskStructPtr subtask);

/*getter and setter*/
Position MessageSubtaskGetPosition(MessageSubtaskStructPtr subtask);
void MessageSubtaskSetPosition(MessageSubtaskStructPtr subtask,Position ppos);
void MessageSubtaskSetPosition2I(MessageSubtaskStructPtr subtask,int posX, int posY);

void MessageSubtaskSetTime(MessageSubtaskStructPtr subtask,double ptime);
void MessageSubtaskSetFontPath(MessageSubtaskStructPtr subtask,const char* fontPath);
void MessageSubtaskSetFontSize(MessageSubtaskStructPtr subtask,int fontSize);
void MessageSubtaskSetColor3I(MessageSubtaskStructPtr subtask,int r, int g, int b);
void MessageSubtaskSetColor(MessageSubtaskStructPtr subtask,Color pcolor);
void MessageSubtaskDestructor(MessageSubtaskStructPtr subtask);

#ifdef __cplusplus
}
#endif

#endif
