#ifndef SKYBOX_H
#define SKYBOX_H

#include "gameobject.h"
#include "vertexdata.h"
#include "material.h"
/**
 * @brief The SkyBox class
 */
class SkyBox : public GameObject
{

public:
    /**
     * @brief SkyBox
     * @param xPos
     * @param yPos
     * @param zPos
     */
    SkyBox(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0);
    /**
     * @brief drawGeometry
     */
    void drawGeometry();
    /**
     * @brief initGeometry
     * @return
     */
    int initGeometry();
    /**
     * @brief setRendermode
     * @param mode
     */
    void setRendermode(int mode);
    /**
     * @brief setMaterial
     * @param materialIn
     */
    void setMaterial(Material *materialIn);
    void GOUpdate(){}
private:
    /**
     * @brief mVertexBuffer
     */
    GLuint mVertexBuffer;
    /**
     * @brief mIndexBuffer
     */
    GLuint mIndexBuffer;
    /**
     * @brief mMaterial
     */
    Material *mMaterial;
    /**
     * @brief mMVPMatrix
     */
    QMatrix4x4 mMVPMatrix;
};

#endif // SKYBOX_H
