#include "PictureList.h"

PictureList::PictureList(int id,
                         int parentId,
                         PluginList* pluginList)
                          : RenderableYobject(id,parentId,pluginList)
{
    posX = 0;
    posY = 0;

    /*init the specifier list*/
    specifierList = new std::unordered_map<std::string,std::vector<Picture*>*>();
    currentPic = nullptr;

    fixedPriority = false;

}


bool PictureList::setCurrentPicture(std::string specifier,int index)
{
    /* try to find the specifier in the list*/
    auto specifierIt = specifierList->find (specifier);

    /* found it*/
    if ( specifierIt != specifierList->end() )
    {
        /* get the current picture on the given index*/
        std::vector<Picture*>* pictureList = specifierIt->second;
        currentPic = (*pictureList)[index];
        return true;
    }

    std::cout <<"\n ERROR:Cant find specifier" << specifier << "\n";
    return false;

}

void PictureList::addPicture(std::string specifier, std::string fileName)
{

    compositor->lockContext();
    
    /*init the picture. need the compositor open gl context for this*/
    Picture* pic = new Picture(fileName,this->posX, this->posY,renderer);

    /*every specifier has a list of pictures, e.g walk.
      test if the specifier exits already or if we have to add a new specifier*/
    auto it = specifierList->find (specifier);

    if ( it != specifierList->end() )
    {
        //specifier exits already
        //just add the picture to the list
        std::vector<Picture*>* pictureList = it->second;
        pictureList->push_back(pic);
    }
    else
    {
        //there is no pictureList under this specifier. create a list
        //and add it to the map
        std::vector<Picture*>* pictureList = new std::vector<Picture*>();
        pictureList->push_back(pic);
        (*specifierList) [ specifier ] = pictureList;
    }

    compositor->freeContext();

}

PictureList::~PictureList()
{

    compositor->lockContext();  

    /*delete the specifier map and it's content. first the content*/
    for (auto specifierIt = specifierList->begin(); 
         specifierIt != specifierList->end();
         specifierIt++)
    {
        //get the current picture list. clear it
        std::vector<Picture*>* pictureList = specifierIt->second;
        for (auto pictureIt = pictureList->begin(); 
             pictureIt != pictureList->end(); 
             pictureIt++)
        {
            delete (*pictureIt);
        }

        delete pictureList;
    }

    //last but not least: kill the specifier map.
    delete specifierList;

    compositor->freeContext();
}

void PictureList::render()
{

    if (currentPic)
    {
        currentPic->setPosition(this->getPosition());
        currentPic->render();
    }

}

Size PictureList::getSize()
{
    if (currentPic)
        return currentPic->getSize();
    else
    {
        Size rec;
        rec.width = -1;
        rec.height = -1;
    }
}

void PictureList::setPosition(Position pos)
{
    setPosition(pos.posX,pos.posY);
}

void PictureList::setPosition(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

Position PictureList::getPosition()
{
    Position pos;
    pos.posX = this->posX;
    pos.posY = this->posY;
    return pos;
}

void PictureList::setRenderPriority(double priority)
{
    fixedPriority = true;
    this->renderPriority = priority;

}


double PictureList::getRenderPriority()
{
    /* because we have the origin of or coordinates on the upper left corner
       we transform it to the lower left corner.*/

    Size size = {0,0}; 

    if (currentPic)
        size = currentPic->getSize();
    
    double prior = 0; 

    if (fixedPriority)
        prior = this->renderPriority;
    else
        prior = this->posY + size.height;

    return prior;

}

bool PictureList::isCurrentPixelTransparent(int x, int y)
{
    if (currentPic)
    {
        //compositor->lockContext();
        bool result = currentPic->isPixelTransparent(x,y);
        //compositor->freeContext();
        return result;

    }
    return true;
}