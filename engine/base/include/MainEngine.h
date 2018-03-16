#ifndef MAINENGINE_H
#define MAINENGINE_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>
#include <list>          // std::list
#include <thread>

#include "Utils.h"

#include <dlfcn.h>

#include "ReloadGamePlugin.h"
#include "TaskManager.h"

#include "PluginList.h"


#define MAINENGINENAME ("MainEngine")

typedef void (*PLUGIN_INIT_PTR)(void* pluginList,
                                void *renderer);

typedef void (*PLUGIN_SIGNAL_RELOAD_PTR)();
typedef void (*PLUGIN_RELOAD_PTR)(void* pluginList,
                                  void *renderer);

typedef void (*PLUGIN_INITPLUGINS_PTR)(void* pluginList);
typedef void (*PLUGIN_MAINLOOP_PTR)(void* pluginList);

class MainEngine :public GameEnginePlugin
{

    public:

        MainEngine();

        void processEvent(SDL_Event& Event);
        int execute();

        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return MAINENGINENAME;}

    private:

    	bool loadPlugin();
        void signalReloadPlugin();
        void reloadPlugin();
        
        bool initLibraries();
        void initGamePlugins();
        bool init();

     	void processMainLoop();

        void cleanup();

        SDL_Window      *window;
        SDL_Renderer    *renderer;

        int screenWidth;
        int screenHeight;

        PluginList* pluginList;

        PLUGIN_INIT_PTR initFunction;
        PLUGIN_SIGNAL_RELOAD_PTR signalReloadFunction;
        PLUGIN_RELOAD_PTR reloadFunction;
        
        PLUGIN_INITPLUGINS_PTR initPluginsFunction;
        PLUGIN_MAINLOOP_PTR mainLoopFunction;


        bool Running;

        bool wasReloaded;

        void* pluginLibrary;
};

#endif // GAME_H
