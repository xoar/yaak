#ifndef CHARACTERINTERFACE_H
#define CHARACTERINTERFACE_H

#include "Position.h"
#include "Rectangle.h"
#include "Size.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct CharacterStruct ;

typedef struct CharacterStruct * CharacterStructPtr;

CharacterStructPtr CharacterConstructor(int id,
                                        const char* name,
                                        void* pluginList);

/*free only the pointer strcut. not deallocate the c++ object*/
void CharacterFreePointerStruct(CharacterStructPtr character);

/* deallocate the c++ object and free the struct*/
void CharacterDestructor(CharacterStructPtr character);

/*for named yojects we need a access only with its id. so for every setter
 getter we povided two interfaces*/

/*the CharacterStructPtr is for generate code*/
/*TODO: unify this!!!*/

Position CharacterGetPosition(CharacterStructPtr character);
Position CharacterGetPositionById(void* pluginList,int id);
        
void CharacterSetPosition(CharacterStructPtr character,
                          Position pos);
void CharacterSetPositionById(void* pluginList,int id,
                          Position pos);

void CharacterSetPosition2I(CharacterStructPtr character,
                          int posX, int posY);
void CharacterSetPosition2IById(void* pluginList,int id,
                          int posX, int posY);

void CharacterAddPicture(CharacterStructPtr character,
                          const char* specifier, 
                          const char* fileName);
void CharacterAddPictureById(void* pluginList,int id,
                          const char* specifier, 
                          const char* fileName);

void CharacterAddAnimationPicture(CharacterStructPtr character,
                                    const char* specifier, 
                                    const char* fileName);
void CharacterAddAnimationPictureById(void* pluginList,int id,
                                    const char* specifier, 
                                    const char* fileName);

int CharacterSetCurrentPicture(CharacterStructPtr character,
                               const char* specifier);
int CharacterSetCurrentAnimationPicture(CharacterStructPtr character,
                               const char* specifier, 
                               int index);
int CharacterSetCurrentPictureById(void* pluginList,int id,
                               const char* specifier);
int CharacterSetCurrentAnimationPictureById(void* pluginList,int id,
                               const char* specifier, 
                               int index);

Size CharacterGetSize(CharacterStructPtr character);
Size CharacterGetSizeById(void* pluginList,int id);

/*TODO: these have only a id interface. add a character struct interface*/
void CharacterLock(void* pluginList,int id);
void CharacterUnlock(void* pluginList,int id);
void CharacterSetStatus(void* pluginList,int id,const char* status);

/*get a copy of the charater state. use free after usage*/
char* CharacterGetStatus(void* pluginList,int id);
int CharacterIsPointInCollider(void* pluginList,int id,Position point);
int CharacterGetId(void* pluginList,char* name);



void CharacterSetCollider(void* pluginList,int id,int width,int height,int heightOffset);


void CharacterSetWalkAnimationFkt(void* pluginList,
                                  int id,
                                  void (*walkAnimation) (Position sourcePosition, 
                                                         Position targetPosition, 
                                                         int totalElapsedTicks, 
                                                         int elapsedTicks));

void CharacterSetRenderPriority(void* pluginList,int id,double priority);

void CharacterActivateCollider(void* pluginList,int id);
void CharacterDeactivateCollider(void* pluginList,int id);

int CharacterCollides(void* pluginList,int id);

#ifdef __cplusplus
}
#endif

#endif

