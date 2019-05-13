#include "CharacterInterface.h"
#include "Character.h"
#include <memory>


/*define the struct. Just a wrapper for the cpp object*/
struct CharacterStruct{
    std::shared_ptr<Character> character;
};

/*its Constructor*/
CharacterStructPtr CharacterConstructor(int id,
                                        const char* name,
                                        void* pluginList)
{
    CharacterStructPtr character  = new CharacterStruct();
    
    character->character = std::make_shared<Character>(id,
                                             std::string(name),
                                             (PluginList*) pluginList);
    character->character->registerYobject(character->character);

    return character;

}

/* helper function*/
std::shared_ptr<Character> getCharacter(void* pluginList,int id)
{
    PluginList* pluginListClass = (PluginList*) pluginList;
    SceneContainer* scene = (SceneContainer*) pluginListClass->get(SceneContainer::getPluginName());

    std::shared_ptr<Yobject> charYobject = scene->getYobject(id);
    std::shared_ptr<Character> character = std::static_pointer_cast<Character>(charYobject);
    return character;
}

//-----------------------

Position CharacterGetPosition(CharacterStructPtr character)
{
    return character->character->getPosition();
}
Position CharacterGetPositionById(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    return character->getPosition();
}
//-----------------------

void CharacterSetPosition(CharacterStructPtr character,
                          Position pos)
{
    character->character->setPosition(pos);
}
void CharacterSetPositionById(void* pluginList,int id,
                          Position pos)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setPosition(pos);
}
//-----------------------

void CharacterSetPosition2I(CharacterStructPtr character,
                          int posX, int posY)
{
    character->character->setPosition(posX,posY);
}
void CharacterSetPosition2IById(void* pluginList,int id,
                          int posX, int posY)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setPosition(posX,posY);
}
//-----------------------

void CharacterAddPicture(CharacterStructPtr character,
                         const char* specifier,
                         const char* fileName)
{
    character->character->addPicture(std::string(specifier),
                                     std::string(fileName));
}
void CharacterAddPictureById(void* pluginList,int id,
                          const char* specifier, 
                          const char* fileName)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->addPicture(std::string(specifier),
                          std::string(fileName));
}
//-----------------------

void CharacterAddAnimationPicture(CharacterStructPtr character,
                                    const char* specifier, 
                                    const char* fileName)
{
    character->character->addAnimationPicture(std::string(specifier),
                                              std::string(fileName));
}
void CharacterAddAnimationPictureById(void* pluginList,int id,
                                    const char* specifier, 
                                    const char* fileName)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->addAnimationPicture(std::string(specifier),
                                  std::string(fileName));
}
//-----------------------

int CharacterSetCurrentAnimationPicture(CharacterStructPtr character,
                               const char* specifier, 
                               int index)
{
    return character->character->setCurrentAnimationPicture(std::string(specifier),index);
}

int CharacterSetCurrentPicture(CharacterStructPtr character,
                               const char* specifier)
{
    return character->character->setCurrentPicture(std::string(specifier));
}

int CharacterSetCurrentPictureById(void* pluginList,int id,
                               const char* specifier)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    return character->setCurrentPicture(std::string(specifier));
}

int CharacterSetCurrentAnimationPictureById(void* pluginList,int id,
                               const char* specifier, 
                               int index)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    return character->setCurrentAnimationPicture(std::string(specifier),index);
}
//-----------------------

Size CharacterGetSize(CharacterStructPtr character)
{
    return character->character->getSize();
}
Size CharacterGetSizeById(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    return character->getSize();
}
//-----------------------

void CharacterLock(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->lock();
}
void CharacterUnlock(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->unlock();
}
void CharacterSetStatus(void* pluginList,int id,const char* status)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setStatus(std::string(status));
}
char* CharacterGetStatus(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    std::string status = character->getStatus();
    /*we have to copy the string, because even we would use a char* pointer by calling c_str on the character class object 
      it liftime is over after a new call of c_str()*/
    return strdup(status.c_str());
}

int CharacterIsPointInCollider(void* pluginList,int id,Position point)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    int status = (int) character->isPointInCollider(point);
    return status;
}

int CharacterGetId(void* pluginList,char* name)
{
    PluginList* pluginListClass = (PluginList*) pluginList;
    SceneContainer* scene = (SceneContainer*) pluginListClass->get(SceneContainer::getPluginName());
    int id = scene->getEntityIdByName(std::string(name));
    return id;
}

void CharacterSetCollider(void* pluginList,int id,int width,int height,int heightOffset)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setCollider(width,height,heightOffset);
}

void CharacterFreePointerStruct(CharacterStructPtr character)
{
    character->character.reset();
    //free(character);
}

void CharacterDestructor(CharacterStructPtr character)
{
    character->character->unregisterYobject(character->character);
    character->character.reset();
    //free(character);
}


void CharacterSetWalkAnimationFkt(void* pluginList,
                                  int id,
                                  void (*walkAnimation) (Position sourcePosition, 
                                                         Position targetPosition, 
                                                         int totalElapsedTicks, 
                                                         int elapsedTicks))
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setWalkAnimationFkt(walkAnimation);
}

void CharacterSetRenderPriority(void* pluginList,int id,double priority)
{

    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->setRenderPriority(priority);
}

void CharacterActivateCollider(void* pluginList,int id)
{

    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->activateCollider();
}

void CharacterDeactivateCollider(void* pluginList,int id)
{

    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    character->deactivateCollider();
}

int CharacterCollides(void* pluginList,int id)
{
    std::shared_ptr<Character> character = getCharacter(pluginList,id);
    return (int) character->collides();
}