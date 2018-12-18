#include "MainEngine.h"
#include <stdio.h>

MainEngine::MainEngine() {

    window = nullptr;

    renderer = nullptr;

    screenWidth= 1024;
    screenHeight = 768;

    Running = true;

    wasReloaded = false;

    pluginList = new PluginList();

    initFunction = nullptr;
    signalReloadFunction = nullptr;
    reloadFunction = nullptr;

    mainLoopFunction = nullptr;
    initPluginsFunction = nullptr;
}



int MainEngine::execute() {
    std::cout << "Execute Main Thread" << std::endl;
   
    if(init() == false) {
        return -1;
    }

    while(Running) {

        processMainLoop();
    }

    cleanup();

    return 0;
}

SDL_Window* MainEngine::getWindow()
{
    return this->window;
}

SDL_Renderer* MainEngine::getRenderer()
{
    return this->renderer;
}

void MainEngine::initGamePlugins()
{
    /** add this object to the pluginlist. needed by the eventsystem*/ 
    pluginList->add(this);

    GameEnginePlugin* reloadPlugin = new ReloadGamePlugin(pluginList);
    pluginList->add(reloadPlugin);

    GameEnginePlugin* taskManager = new TaskManager(pluginList);
    pluginList->add(taskManager);

}

bool MainEngine::initLibraries()
{
    if (SDL_Init(SDL_INIT_EVERYTHING  & ~SDL_INIT_AUDIO) < 0) {
        logSDLError(std::cout,"SDL Iinit");
        return false;
    }

    if ((window = SDL_CreateWindow("Hello World!", 100, 100,
         screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == nullptr)
    {
        logSDLError(std::cout, "Create Window");
        return false;
    }


    if ((renderer = SDL_CreateRenderer(window, -1,
         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr)
    {
        logSDLError(std::cout,"Create Renderer");
        return false;
    }


    if (TTF_Init() == -1)
    {
        std::cout << TTF_GetError() << std::endl;
        return false;
    }

    return true;

}

bool MainEngine::init()
{

    /** init sdl, ttf and image stuff*/
    if(!initLibraries()) return false;
    
    /** init the plugins. some of them can only be initialiezed after the sdl initialization
     * Thats the reason wy this be done here
     */
    this->initGamePlugins();

    /* set the load and reload function pointer and load the plugin*/
    if (!loadPlugin()) return false;

    /*exec the init function in the plugin*/
    initPluginsFunction(pluginList);

    /* start the plugin's init fct*/
    std::cout << "start normal init function" << std::endl;
    initFunction( ((void*) pluginList),((void*)renderer)  );
    
    return true;
}

bool MainEngine::loadPlugin()
{
    std::cout << "\nload library"<< std::endl;

    /* open the library*/
    pluginLibrary = dlopen("libplugin.so", RTLD_LAZY);
    
    if (pluginLibrary == NULL) {
        std::cout << "Cant open plugin" << dlerror() << std::endl;
        return false;
    } 

    char *error;
    void* initializer;


    /*set the initFunction pointer*/
    initializer = dlsym(pluginLibrary,"pluginInit");
    if ((error = dlerror()) != NULL)
    {
        std::cerr << "Cant access init function" << std::endl;
        dlclose(pluginLibrary);
        return false;
    } 

    initFunction = (PLUGIN_INIT_PTR) initializer;
            

    /*set the reload pointer*/
    initializer = dlsym(pluginLibrary,"signalPluginReload");
    if ((error = dlerror()) != NULL)
    {
        std::cerr << "Cant access reload function" << std::endl;
        dlclose(pluginLibrary);
        return false;
    } 

    signalReloadFunction = (PLUGIN_SIGNAL_RELOAD_PTR) initializer;


    /*set the init plugins pointer*/
    initializer = dlsym(pluginLibrary,"initPlugins");
    if ((error = dlerror()) != NULL)
    {
        std::cerr << "Cant access initPlugins function" << std::endl;
        dlclose(pluginLibrary);
        return false;
    } 

    initPluginsFunction = (PLUGIN_INITPLUGINS_PTR) initializer;

    /*set the main loop pointer*/
    initializer = dlsym(pluginLibrary,"mainLoop");
    if ((error = dlerror()) != NULL)
    {
        std::cerr << "Cant access mainLoop function" << std::endl;
        dlclose(pluginLibrary);
        return false;
    } 

    mainLoopFunction = (PLUGIN_MAINLOOP_PTR) initializer;



    /* try to get the reload function. if it is not declared use the init function
       instead */

    initializer = dlsym(pluginLibrary,"reloadInit");
    
    if ((error = dlerror()) != NULL)
    {
        std::cout << "Cant access reload function" << std::endl;
        std::cout << "Use the init function instead" << std::endl;

        reloadFunction = initFunction;
    } 
    else
        reloadFunction = (PLUGIN_RELOAD_PTR) initializer;

    return true;

}


/** is called by the game event plugin */
void MainEngine::processEvent(SDL_Event& Event) {
    
    if(Event.type == SDL_QUIT) {
        Running = false;
    }

    if(Event.type == SDL_KEYUP)
    {
        /*signal reaload key*/
        /* NOTE: This is processed before every task is processed*/
        if (Event.key.keysym.sym == SDLK_F2)
            signalReloadPlugin();
    }


}

void MainEngine::signalReloadPlugin()
{
    std::cout << "\nsignal reload" << std::endl;

    /*subtasks can check if a reload is processing */
    ((ReloadGamePlugin*) pluginList->get( ReloadGamePlugin::getPluginName() ))->setReloadStatus(true);

    /* The task must proccess once to receive the kill signal. 
       after processing the plugin is reloaded in processReload()*/
    
    /*kill all threads*/
    std::vector<std::string> nameList;
    ((TaskManager*) pluginList->get( TaskManager::getPluginName() ))->killAllTaskExcept(nameList);

    /*clear the plugins and signal a reload to the plugin*/
    signalReloadFunction();

    
}

void MainEngine::reloadPlugin()
{

    std::cout << "\nprocess reload "<< std::endl;

    /*delete the pluginList*/
    pluginList->clear();

    /*close the plugin and load it again*/
    std::cout << "\nclose library"<< std::endl;
    dlclose(pluginLibrary);

    /*recompile the plugin*/
    /*TODO: add a case  for windows support*/
    std::cout << "\nrecompile library"<< std::endl;
    system("./recompile");

    /*init the Pluginlist like the Taskmanager*/
    initGamePlugins();

    /*load the plugin again but use the reload fct if present*/
    std::cout << "\nload library again"<< std::endl;
    loadPlugin(); 


    /*exec the init function in the plugin*/
    initPluginsFunction(pluginList);

    /* start the plugin's init fct*/
    //std::cout << "start normal init function" << std::endl;
    //initFunction( ((void*) pluginList),((void*)renderer)  );

    /* signal that the reload is over*/
    ((ReloadGamePlugin*) pluginList->get( ReloadGamePlugin::getPluginName() ))->setReloadStatus(false);


    std::cout << "Start reload init" << std::endl;
    reloadFunction( ((void*) pluginList),((void*)renderer));

}

void MainEngine::processMainLoop()
{
    /* process the main loop in the plugin*/
    mainLoopFunction(pluginList);

    /* check if a reload of the plugin should be done*/
    bool reload = ((ReloadGamePlugin*) pluginList->get( ReloadGamePlugin::getPluginName() ))->getReloadStatus();

    if (reload)
        reloadPlugin();
        
}

void MainEngine::cleanup() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
