#include "MainEngine.h"

int main(int argc, char* argv[]) {
    MainEngine game;

    /*start the main loop in a thread*/
    std::thread t(&MainEngine::execute,&game);
    t.join();

}