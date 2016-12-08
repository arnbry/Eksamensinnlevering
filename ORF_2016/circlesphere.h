#ifndef CIRCLESPHERE_H
#define CIRCLESPHERE_H

#include "gameobject.h"
#include "vertexdata.h"
#include "material.h"
/**
 * @brief The CircleSphere class
 */
class CircleSphere : public GameObject
{
public:
    /**
     * @brief CircleSphere
     * @param resolution
     * @param xPos
     * @param yPos
     * @param zPos
     */
    CircleSphere(int resolution = 1, float xPos = 0.0, float yPos = 0.0, float zPos = 0.0);
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
     * @brief setResolution
     * @param resolution
     */
    void setResolution(int resolution);
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
    /**
     * @brief mVertexPrCircle
     */
    int mVertexPrCircle;
    /**
     * @brief mRadius
     */
    float mRadius = 3.0f;
    /**
     * @brief mNoIndices
     */
    int mNoIndices;

    QVector3D mColor{0.0f, 1.0f, 0.0f};
};

#endif // CIRCLESPHERE_H
