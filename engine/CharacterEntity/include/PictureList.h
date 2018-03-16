#ifndef PICTUREYOBJECT_H
#define PICTUREYOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "Size.h"

#include "Picture.h"
#include "RenderableEntity.h"


class PictureList:public RenderableYobject
{
    public:
        PictureList(int id,int parentId,PluginList* pluginList);

        virtual ~PictureList();

        Position getPosition();
        void setPosition(Position pos);
        void setPosition(int posX, int posY);

        /*get the size of the current picture*/
        Size getSize();

        /* add a picture with a specifier. 
           the specifier is used for referencing.
           The pictures are used for standing, looking in a directions, ...
        
           if the specifier is already used, the picture is add to the list 
           under this specicifer

           the current displayed picture is set to the given picture*/
        void addPicture(std::string specifier, std::string fileName);


        /*set the current displayed picture. 
          return true if the specifier was found,
          else false. */
        virtual bool setCurrentPicture(std::string specifier,int index);

        void render();
    protected:
        int posX;
        int posY;

        /* pointer to the current picture which will be rendered*/
        Picture* currentPic;

        /*normal Pictures used for standing and looking in a direction*/
        std::unordered_map<std::string,std::vector<Picture*>*>* specifierList;


    private:
};

#endif // PICTURE_H
