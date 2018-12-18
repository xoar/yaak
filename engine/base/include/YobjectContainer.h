#ifndef YOBJECTCONTAINER_H
#define YOBJECTCONTAINER_H

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::list
#include "Utils.h"
#include "GameEnginePlugin.h"
#include "Yobject.h"
#include <mutex>
#include <memory>

#include <exception>
#include <cstdlib>

class YobjectContainer: public GameEnginePlugin
{

public:
    YobjectContainer()
    {
        yobjectList = new std::vector<std::shared_ptr<Yobject>>();
    }

    ~YobjectContainer()
    {
        freeList();
    }

    void removeYobject(std::shared_ptr<Yobject> yobject)
    {
        /* avoid race: iterating while other threads remove yobjects */
        std::lock_guard<std::recursive_mutex> lock(containerMutex);

        try {
            std::vector<std::shared_ptr<Yobject>>::iterator nextIt;

            for (auto it = yobjectList->begin(); it != yobjectList->end(); it=nextIt)
            {
                if ((*it) == yobject)
                    nextIt = yobjectList->erase(it);
                else
                    nextIt= std::next(it);
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "\n cant remove yobject " << e.what() << '\n';
            std::exit(EXIT_FAILURE);
        }
    }

    void addYobject(std::shared_ptr<Yobject> yobject)
    {
        std::lock_guard<std::recursive_mutex> lock(containerMutex);

        yobjectList->push_back(yobject);
    }

    std::shared_ptr<Yobject> getYobject(int id)
    {
        std::lock_guard<std::recursive_mutex> lock(containerMutex);
        
        for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
        {
            if ((*it)->getId() == id)
                return (*it);
        }

        std::cerr << "\n cant find yobject: " << id << '\n';
        std::exit(EXIT_FAILURE);
    }

    std::shared_ptr<Yobject> getYobject(int id,int parentId)
    {
        std::lock_guard<std::recursive_mutex> lock(containerMutex);
        
        for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
        {
            if ((*it)->getParentId() == parentId)
                if ((*it)->getId() == id)
                    return (*it);
        }

        std::cerr << "\n cant find yobject: id: " << id << "parentId :"<< parentId <<"\n";
        std::exit(EXIT_FAILURE);
    }

    int getEntityIdByName(std::string name)
    {
        /*nobody should change the list while iterating*/
        std::lock_guard<std::recursive_mutex> lock(containerMutex);
            
        for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
        {
                if ((*it)->getType() == "Entity")
                {
                    /*std::cerr << "have entity with name: " << ((*it))->getName() 
                              << " and id " << (*it)->getId() << "\n";*/
                    if (name == ((*it))->getName())
                        return (*it)->getId();
                }
        }

        std::cerr << "\nCan't find Entity: " << name << '\n';
        std::exit(EXIT_FAILURE);

    }

    void deleteAllEntities()
    {
        /*nobody should change the list while iterating*/
        std::lock_guard<std::recursive_mutex> lock(containerMutex);
            
        std::vector<std::shared_ptr<Yobject>>::iterator nextIt;

        for (auto it = yobjectList->begin();it != yobjectList->end(); it=nextIt)
        {
                std::cout << "try to delete: " << (*it)->getType() << " id: " 
                          << (*it)->getId() << std::endl;
                
                if ((*it)->getType() == "Entity")
                {
                    /* if a yobject owns for some reasons other yobjects, the
                    iteration broke, so we start from the beginning.*/
                    std::cout << "delete entity " << (*it)->getId() << std::endl; 
                    yobjectList->erase(it);
                    nextIt = yobjectList->begin();

                }
                else
                    nextIt= std::next(it);
        }

    }


    /* clear the list and free all yobjects. used by a reload*/
    void freeList()
     {
        std::lock_guard<std::recursive_mutex> lock(containerMutex);

        /* if a yobject owns for some reasons other yobjects, the
           iteration broke, so we just kill the first element.*/

        /*of course we could just use the clear method, but this lead
          to broken remove calls of this container by deleting an element*/

        try {

            for (auto it = yobjectList->begin(); it != yobjectList->end(); 
            	 it = yobjectList->begin())
            {
                yobjectList->erase(it);
            }

            yobjectList->clear();
        }
        catch (std::exception& e)
        {
            std::cerr << "\n cant remove yobject " << e.what() << '\n';
            std::exit(EXIT_FAILURE);
        }

    }

    virtual std::string getName() {}

protected:
    std::vector<std::shared_ptr<Yobject>>* yobjectList;

    /* when deleting an entity in freeList it can call the yobject containers
       remove function. so we need a recursive mutex*/
    std::recursive_mutex containerMutex;
};

#endif // YOBJECTCONTAINER_H