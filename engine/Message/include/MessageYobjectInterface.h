#ifndef MESSAGEYOBJECTINTERFACE_H
#define MESSAGEYOBJECTINTERFACE_H

#include "Position.h"
#include "Rectangle.h"
#include "Color.h"

#ifdef __cplusplus
extern "C" 
{
#endif


/*foward the declaration. definition is done in the corresponding c file*/
struct MessageYobjectStruct ;

typedef struct MessageYobjectStruct * MessageYobjectStructPtr;

MessageYobjectStructPtr MessageYobjectConstructor(int id,
                                                  int parentId,
                                                  const char* text,
                                                  int characterId,
                                                  void* pluginList);

/** the the active status. active by default*/
void MessageYobjectActivate(MessageYobjectStructPtr message);

void MessageYobjectDeactivate(MessageYobjectStructPtr message);

void MessageYobjectGetSize(MessageYobjectStructPtr message,
                           int* width, int* height);

void MessageYobjectDestructor(MessageYobjectStructPtr message);

/*free only the pointer strcut. not deallocate the c++ object*/
void MessageYobjectFreePointerStruct(MessageYobjectStructPtr message);


Position MessageYobjectGetPosition(MessageYobjectStructPtr message);
void MessageYobjectSetPosition(MessageYobjectStructPtr message,Position ppos);
void MessageYobjectSetPosition2I(MessageYobjectStructPtr message,int posX, int posY);

void MessageYobjectSignalInitRessources(MessageYobjectStructPtr message);

void MessageYobjectSetFontSize(MessageYobjectStructPtr message,int fontSize);

void MessageYobjectSetColor3I(MessageYobjectStructPtr message,int r, int g, int b);
void MessageYobjectSetColor(MessageYobjectStructPtr message,Color pcolor);

#ifdef __cplusplus
}
#endif

#endif