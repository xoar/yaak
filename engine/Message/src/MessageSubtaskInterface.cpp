#include "MessageSubtaskInterface.h"

/*include the cpp variant*/
#include "MessageSubtask.h"


/*define the struct. Just a wrapper for the cpp object*/
struct MessageSubtaskStruct{
    MessageSubtask* subtask;
};

/* the Constructor*/
MessageSubtaskStructPtr MessageSubtaskConstructor(void* pluginList,
                                         int id,
                                         const char* text,
                                         int characterId,
                                         const char* eventName)
{

    //struct MessageStruct subtask;

    MessageSubtaskStructPtr subtask  =  (MessageSubtaskStructPtr) malloc(sizeof(struct MessageSubtaskStruct));

    subtask->subtask = new MessageSubtask((PluginList*) pluginList,
                                         id,
                                         std::string(text),
                                         characterId,
                                         std::string(eventName));
    return subtask;

}

/** this is the process function which must be overriden
    to implement the disired functionality */

int MessageSubtaskProcess(MessageSubtaskStructPtr subtask)
{
    try
    {
      subtask->subtask->process();
    }
    catch (KillException& e)
    {
        /* if a kill was signaled return this
           to the caller so the thread can terminate*/
        
        /*free the ressource 
          because it was a heap allocation its not done automatically*/
        std::cout << "Message recive kill signal" << std::endl;
        MessageSubtaskDestructor(subtask);
        return 0;
    }

    /*normal exit without a kill*/
    MessageSubtaskDestructor(subtask);
    return 1;
}

/*getter and setter*/
Position MessageSubtaskGetPosition(MessageSubtaskStructPtr subtask)
{
    return subtask->subtask->getPosition();
}
void MessageSubtaskSetPosition(MessageSubtaskStructPtr subtask,Position pos)
{
    subtask->subtask->setPosition(pos);
}
void MessageSubtaskSetPosition2I(MessageSubtaskStructPtr subtask,int posX, int posY)
{
    subtask->subtask->setPosition(posX,posY);
}
void MessageSubtaskSetTime(MessageSubtaskStructPtr subtask,double time)
{
    subtask->subtask->setTime(time);
}
void MessageSubtaskSetFontPath(MessageSubtaskStructPtr subtask,const char* fontPath)
{
    subtask->subtask->setFontPath(std::string(fontPath));
}
void MessageSubtaskSetFontSize(MessageSubtaskStructPtr subtask,int fontSize)
{
    subtask->subtask->setFontSize(fontSize);
}
void MessageSubtaskSetColor3I(MessageSubtaskStructPtr subtask,int r, int g, int b)
{
    subtask->subtask->setColor(r,g,b);
}
void MessageSubtaskSetColor(MessageSubtaskStructPtr subtask,Color color)
{
    SDL_Color sdlColor;
    sdlColor.r = color.r;
    sdlColor.g = color.g;
    sdlColor.b = color.b;
    subtask->subtask->setColor(sdlColor);
}

void MessageSubtaskDestructor(MessageSubtaskStructPtr subtask)
{
    delete subtask->subtask;
    free(subtask);
}