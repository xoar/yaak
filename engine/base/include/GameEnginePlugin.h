#ifndef GAMEENGINEPLUGIN_H
#define GAMEENGINEPLUGIN_H

#include <string>

class GameEnginePlugin
{
    public:

        GameEnginePlugin() {}
        virtual ~GameEnginePlugin() {}
        /** the unique Name of the Plugin. have to be overidden */
        virtual std::string getName() {};

};

#endif // GAMEENGINEPLUGIN_H
