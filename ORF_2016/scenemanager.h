#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//#include "camera.h"

class Camera;
class scenenode;



class SceneManager
{
public:

    void UpdateAll();
    void Draw();

    static SceneManager *getInstance();

private:
    Camera* camera;
    scenenode* activScene;
    SceneManager();
    static SceneManager *mInstance;

};

#endif // SCENEMANAGER_H
