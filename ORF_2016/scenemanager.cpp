#include "scenemanager.h"
#include "scenenode.h"
#include "gameobject.h"

SceneManager* SceneManager::mInstance =0;

SceneManager* SceneManager::getInstance()
{

    if (!mInstance)
    {
        mInstance = new SceneManager();

    }
    return mInstance;
}

SceneManager::SceneManager()
{
}


void SceneManager::UpdateAll()
{

}

void SceneManager::Draw()
{

}
