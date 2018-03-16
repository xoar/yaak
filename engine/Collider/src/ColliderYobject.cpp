#include "ColliderYobject.h"
#include "ColliderPlugin.h"

ColliderYobject::ColliderYobject (int id,
								  int parentId,
								  std::string type,
								  PluginList* pluginList)
  								   :Yobject(id,parentId)
{

    colliderPlugin = (ColliderPlugin*) pluginList->get( ColliderPlugin::getPluginName());
    this->type = type;

}

ColliderYobject::~ColliderYobject()
{
    /*unregister has been done before*/
}

void ColliderYobject::registerYobject(std::shared_ptr<ColliderYobject> yobject)
{
    /*add the collider to the plugin list */
    colliderPlugin->addYobject(yobject);
}

void ColliderYobject::unregisterYobject(std::shared_ptr<ColliderYobject> yobject)
{
    /*remove the yobject to the render queue*/
    colliderPlugin->removeYobject(yobject);
}


bool ColliderYobject::isPointInCollider(Position point) {}
bool ColliderYobject::collidesWith(std::shared_ptr<ColliderYobject> collider) {}


std::string ColliderYobject::getType()
{
	return this->type;
}

bool ColliderYobject::collides(std::shared_ptr<ColliderYobject> collider)
{
    return colliderPlugin->collides(collider);
    return false;
}