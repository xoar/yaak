# Yaak
Yaak or Yet another adventure kit is a simple C language extension framework for game development.

With yaak you can mix C code with an easy to use DSL, e.g by writing

```C
System talks "*Prolog ... bla bla bla ... some previous history ...*" 
        time : 4.0s 
        size : 50 
        color : 255, 144, 0
```

for a message from the system.
The core of yaak is BeyondC, a modular C language extension framework.
Similar to this project is mbeddr (http://mbeddr.com/), but with the difference that yaak is not eclipse bounded and uses text files.

To see some examples of the mixture of C and the DSL, see the file game/src/Scene1.c

#Install Guide
create the eli subsystem by running BeyondC/tools/build eli.sh
create the compiler by running BeyondC/build compiler.sh
build the libaries ./installLibaries
and build the game by running ./build

You must have a tcl interpreter installed and the tk window system for tcl

#Run the game
Use the starter script yaakstarter in the bin folder, to start the game.

Edit the game/src files to change the game logic.

#add a new DSL module
 TODO

#Issues

  When you have trouble to link against the SDL libraries, the lib folders could be missing.
  create them by running ln -s lib64 lib in lib/SDL2, lib/SDL_ttf and lib/SDL_image
