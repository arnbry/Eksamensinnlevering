#ifndef SCENENODE_H
#define SCENENODE_H

#include "gameobject.h"
#include "qvector3d.h"

class scenenode
{
public:
    scenenode();
    void PushGameobject(GameObject* gameObject);

private:
    float width;
    float height;
    QVector3D pos;
    std::vector<GameObject*> gameObjects;
};

#endif // SCENENODE_H
