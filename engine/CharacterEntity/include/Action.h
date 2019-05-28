#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

/* Wait is the default State. then when the action should be processed its set to Ready
   by the Character. Then You should set it to Running. when somebod try to abort all actions
   it could be set to Aborted from another task. After finishing you should set it to finish and deque
   the action from the queue.*/ 
enum ActionState { Wait, Ready, Running, Finished, Aborted};



/* action on a Character which will be processed by subtask.
   All action executed by subtask on a Character have to inherit this class
   an enque the action via Character::enqueueAction().*/
class Action
{

    public:
        /* each action has a identifier string for the enqueue decision by the Character*/
        Action(std::string type)
        {
            this->type = type;
            abortMessage = "";
            state = "Wait";
        };

        /* signal abort. only the process started the action can abort it and clean it up*/
        void signalAbort(){state = "Aborted";}

        /* when aborting you can communicate the reason 
           e.g the action which will be execute instead */
        void setAbortMessage(std::string message) {abortMessage = message;}

        /* get the abort message*/
        std::string getAbortMessage(){return abortMessage;}

        /*get the type*/
        std::string getType(){return type;}

        /*set the state*/
        void setState(std::string state){this->state=state;}

        std::string getState(){return state;}

    protected:
        std::string abortMessage;
        std::string type;
        std::string state;

};

#endif