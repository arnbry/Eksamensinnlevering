#ifndef CUBEGOBJECT_H
#define CUBEGOBJECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "transform.h"
#include "gameobject.h"
#include "vertexdata.h"

class CubeGObject : public GameObject
{
public:
    CubeGObject(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0);

    void drawGeometry(QOpenGLShaderProgram *program);
    /**
      initVertexBufferObjects() calls glGenBuffers(), glBindBuffer() and glBufferdata()
      for using later use of glDrawArrays()
     */
    void initVertexBufferObjects();


    /*!
     * \brief update is empty so i dont have to implement it later. i think of it as start() and update() in unity scripts.
     *  as update will happen and update itself every Frame
     */
    void update(){}

private:
    void initGeometry();

    QMatrix4x4 mModelMatrix;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    int mNVertices;
    VertexData* mVertices;

};

#endif // CUBEGOBJECT_H
