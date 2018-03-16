#include "stdio.h" /*balabababa between*/
#include "Talk.h"


extern "C" {
extern int printf (const char * __restrict __format,...) throw() ;
}

__extension__ extern int printb (const char * __restrict __format,...) throw() ;

typedef struct
{
    int posX;
    int posY;
} Position;

struct SettingsValue
{
    int intValue;
    double doubleValue;
    Position positionValue;
    /*kcukst du weiter*/
    const char *stringValue;
};
/*my little comment*/
void MylittleEvent()
{
    Character Yoda
      picture "standing" : "../res/yoda.gif"
      position: 70, 480
  
    Character Luke
      picture "standing" : "../res/luke.gif"
      position : 300, 300
      /*even moooore*/
}


/*more comments*/
int main() /*balasdawd*/
{
  int a;
  
  /*some test*/

  struct SettingsValue defaultPos;
  /*blaa*/
  Position standardPosition = {10,20 };
  defaultPos.positionValue = standardPosition;

  printf("Hello world\n");
  a = (42) + (5*(6+7)) + 5*((5));

   if (a <0)
   {
        Yoda talks to Luke "fuck you"
         while (a >0)
         {
             Yoda talks to Luke "fuck you"
         }
   }
  return 0;
}
