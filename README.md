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
Similar to this project is mbeddr (http://mbeddr.com), but with the difference that yaak is not eclipse bounded and uses text files.

To see some examples of the mixture of C and the DSL, see the file game/src/Scene1.c

# Install Guide
create the eli subsystem by running BeyondC/tools/build\ eli.sh \
create the compiler by running BeyondC/build\ compiler.sh \
build the libaries ./installLibaries \
and build the game by running ./build \

You must have a tcl interpreter installed and the tk window system for tcl

# Run the game
Use the starter script yaakstarter in the bin folder, to start the game.

Edit the game/src files to change the game logic.

# Add a new DSL module

  We first try to add a macro like module shoot.
  Therefore you have to create a folder Shoot in BeyondC/modules and add these two files:


BeyondC/modules/Shoot/ShootLanguage.fw:
```
@p maximum_input_line_length = infinity

@O@<ShootGrammer.con@>==@{

    Subtask: ShootSubtask.
    
    ShootSubtask: 'shoot'.

@}
```

BeyondC/modules/Shoot/ShootUnparser.fw:
```
@p maximum_input_line_length = infinity


@O@<ShootLanguage.lido@>==@{

    RULE: ShootSubtask::= 'shoot' COMPUTE
        ShootSubtask.IdemPtg = PTGShootPrinter();
    END;
@}


@O@<ShootLanguage.ptg@>==@{

ShootPrinter:
    "    printf(\"Shoot them\");"
@}
```

The first file describes the grammar in bnf.
Every statement in an event is derived from Subtask.

In the second file we describe how the unparser handles our DSL snippet. A unparser normally take the parsed AST and print it in a text representation.
Our unparser should take the C and DSL AST and transform it to C code only.

Therefore every node in the parsed AST have a attribute IdemPtg
which have a text representation of the node.

We just have to change this text representation. Without this change IdemPtg would contain the text "shoot".

Therefor we have `ShootSubtask.IdemPtg = PTGShootPrinter();`
The function PTGShootPrinter() is build in the ShootLanguage.ptg section.
It's just a text generator description.
Every section like ShootPrinter builds a text generator with the same name as the section and the prefix PTG.

Finally we have to add the two files into the compiler construction by adding the line
`BeyondC/modules/Shoot/ShootLanguage.fw:` to BeyondC/language.specs and `modules/Shoot/ShootUnparser.fw` to BeyondC/unparser.specs.

Now run BeyondC/build compiler.sh and bin/recompile and test the new language item.

#Dependencies

Clang and because we use SDL2,SDL_image and SDL_ttf you should install their dependencies.
For SDL2 see https://wiki.libsdl.org/Installation.
Freetype is shipped with this project.


# Issues

  When you have trouble to link against the SDL libraries, the lib folders could be missing.
  create them by running ln -s lib64 lib in lib/SDL2, lib/SDL_ttf and lib/SDL_image
