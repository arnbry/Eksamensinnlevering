#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <QOpenGLFunctions>
#include "vertexdata.h"
#include "material.h"

class GameObject;
/**
 * @brief The BoundingVolume class
 */
class BoundingVolume : protected QOpenGLFunctions
{
public:
    /**
     * @brief BoundingVolume
     */
    BoundingVolume();

    /**
     * @brief initGeometry
     * @param mVertexData
     * @param triangles
     * @return
     */
    int initGeometry(const VertexData *mVertexData, int triangles);
    /**
     * @brief drawGeometry
     * @param mMaterial
     */
    void drawGeometry(Material *mMaterial);

private:
    /**
     * @brief mVertexBuffer
     */
    GLuint mVertexBuffer;
    /**
     * @brief mIndexBuffer
     */
    GLuint mIndexBuffer;
};

#endif // BOUNDINGVOLUME_H
