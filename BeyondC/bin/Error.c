

typedef struct
{
    int posX;
    int posY;
} Position;


typedef struct
{
    int r;
    int g;
    int b;
} Color;


void Hello()
{

    int a;
}

Event IntroduceBernard
{
/*create Bernard*/
    Character Bernard
      picture "standing right" : "../res/Standright.png"
      picture "standing left" : "../res/Standleft.png"

      pos : 300, 50

      animation "walking right":  "../res/WR1.png",
                                  "../res/WR2.png",
                                  "../res/WR3.png",
                                  "../res/WR4.png",
                                  "../res/WR5.png",
                                  "../res/WR6.png"

    Bernard set current animation picture to "walking right" with index 3

    int b;

    Hello();
}


void test()
{
    int a;
    IntroduceBernard();

}

int index;

struct MessageStruct ;

typedef struct MessageStruct * MessageStructPtr;


MessageStructPtr MessageConstructor(void* pluginList,
                                    int id,
                                    const char* text,
                                    int characterId,
                                    double time,
                                    const char* fontPath,
                                    Position pos,
                                    int fontSize,
                                    Color color,
                                    const char* eventName,
                                    void *renderer);