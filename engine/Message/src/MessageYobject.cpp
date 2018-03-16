#include "MessageYobject.h"
#include <stdexcept>

MessageYobject::MessageYobject(int id,
                               int parentId,
                               std::string text,
                               int characterId,
                               PluginList* pluginList)
                                : RenderableYobject(id,parentId,pluginList)
{
    GlobalSettings* globalSettings = nullptr;
    try
    {
        /*load the defaults.*/
        globalSettings = (GlobalSettings*) pluginList->get(GlobalSettings::getPluginName());
    }
    catch(std::runtime_error& e)
    {
        std::cerr <<"ERROR: Cant find the global Settings, subtask id: "<< id 
        << ", "  << e.what() << "\n";
    }


    union SettingsValue defaultPos = globalSettings->getSetting("DefaultPosition");
    union SettingsValue defaultSize = globalSettings->getSetting("DefaultSize");
    union SettingsValue defaultColor = globalSettings->getSetting("DefaultColor");
    union SettingsValue defaultFontPath = globalSettings->getSetting("DefaultFont");

    /*transform the color to a sdl color*/
    SDL_Color sdlColor;
    sdlColor.r = defaultColor.colorValue.r;
    sdlColor.g = defaultColor.colorValue.g;
    sdlColor.b = defaultColor.colorValue.b;

    /*build the message, the texture will be created later by calling InitRessources()*/
    this->message = new Message(text,
                                defaultFontPath.stringValue,
                                defaultPos.positionValue.posX,
                                defaultPos.positionValue.posY,
                                defaultSize.intValue,
                                sdlColor,
                                this->renderer /*init by rederableYobject*/
                                );

    if (characterId > -1)
    {
        try
        {
            SceneContainer* scene = (SceneContainer*) pluginList->get(SceneContainer::getPluginName());
            std::shared_ptr<Yobject> charYobject = scene->getYobject(characterId);

            this->owner = std::static_pointer_cast<Character>(charYobject);
        }
        catch(std::runtime_error& e)
        {
            std::cerr <<"ERROR: Cant find the Scene Editor, subtask id: "<< id 
            << ", "  << e.what() << "\n";
        }
    }
    
    fixedTextPosition = false;
    hasInitializedRessources = false;
}


MessageYobject::~MessageYobject()
{
    /*signal the destruction of the message*/
    /*should be killed now... after the deletion of the message 
      you cant call the function*/
    signalFreeRessourcesNow();

    delete message;
}

void MessageYobject::initRessources()
{
    message->createTexture();
    hasInitializedRessources = true;
}

void MessageYobject::freeRessources()
{
    message->destroyTexture();
    hasInitializedRessources = false;
}

void MessageYobject::getSize(int & width, int & height)
{
    /*return -1,-1 if it has no texture*/
    message->getSize(width,height);
}


void MessageYobject::render()
{

    /* display the text over the owner */
    /* TODO : clac an offset */
    if ((owner) && (!this->fixedTextPosition))
    {
        Position p = owner->getPosition();
        p.posY -= 50;
        message->setPosition(p);
    }
    
    message->render();
}

void MessageYobject::setPosition(Position pos)
{
    this->message->setPosition(pos);
}

void MessageYobject::setPosition(int posX, int posY)
{
    this->message->setPosition(posX, posY);
}

Position MessageYobject::getPosition()
{
    return this->message->getPosition();
}

void MessageYobject::setFontPath(std::string fontPath)
{
    this->message->setFontPath(fontPath);
    /* need a new build of the message*/
    if (hasInitializedRessources) signalInitRessourcesNow();
}

void MessageYobject::setFontSize(int fontSize)
{
    this->message->setFontSize(fontSize);
    /* need a new build of the message*/
    if (hasInitializedRessources) signalInitRessourcesNow();
}

void MessageYobject::setFixTextPosition(bool fixedTextPosition)
{
    this->fixedTextPosition = fixedTextPosition;
}

void MessageYobject::setColor(int r, int g, int b)
{
    this->message->setColor(r,g,b);
}

void MessageYobject::setColor(SDL_Color color)
{
    this->message->setColor(color);
    /* need a new build of the message*/
    if (hasInitializedRessources) signalInitRessourcesNow();
}
