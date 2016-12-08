#ifndef AXESGIZMO_H
#define AXESGIZMO_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "transform.h"
#include "gameobject.h"
#include "material.h"

/**
 * @brief The AxesGizmo class
 */
class AxesGizmo : public GameObject
{
    //Q_OBJECT
public:
    /**
     * @brief AxesGizmo
     * @param xPos
     * @param yPos
     * @param zPos
     */
    AxesGizmo(float xPos = 0.0f, float yPos = 0.0f, float zPos = 0.0f);
    /**
     * @brief drawGeometry
     */
    void drawGeometry();
    /**
     * @brief setMaterial
     * @param materialIn
     */
    void setMaterial(Material *materialIn);
    /**
     * @brief setRendermode
     * @param mode
     */
    void setRendermode(int mode){}
private:
    /**
     * @brief initGeometry
     * @return
     */
    int initGeometry();
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

#endif // AXESGIZMO_H
