#include "scenenode.h"

scenenode::scenenode()
{

}

void scenenode::PushGameobject(GameObject *gameObject)
{
    gameObjects.push_back(gameObject);

}


