#include "axesgizmo.h"

#include <QVector2D>
#include <QVector3D>

#include "vertexdata.h"

AxesGizmo::AxesGizmo(float xPos, float yPos, float zPos)
{
    mTransform = new Transform(this);
    mTransform->setPosition(QVector3D(xPos, yPos, zPos));

    initGeometry();
    getMatrix();
}

int AxesGizmo::initGeometry()
{
    //Format: Position, UV, Normal
/*
    mVertices->set_xyz(-500.0f*mTransform->getScale().x(), 0.0f,  0.0f);
    mVertices->set_normal(1.0f, 0.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);

    mVertices->set_xyz(500.0f*mTransform->getScale().x(), 0.0f,  0.0f);
    mVertices->set_normal(1.0f, 0.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);

    mVertices->set_xyz(0.0f,-500.0f*mTransform->getScale().y(),  0.0f);
    mVertices->set_normal(0.0f, 1.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);

    mVertices->set_xyz(0.0f,500.0f*mTransform->getScale().y(),  0.0f);
    mVertices->set_normal(0.0f, 1.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);

    mVertices->set_xyz(0.0f,-500.0f*mTransform->getScale().z(),  0.0f);
    mVertices->set_normal(0.0f, 1.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);

    mVertices->set_xyz(0.0f,0.0f,-500.0f*mTransform->getScale().z());
    mVertices->set_normal(0.0f, 1.0f,  0.0f);
    mVertices->set_st(0.0f, 0.0f);
    */
    VertexData vertices[] = {

        // Vertex data for X-axix
        {QVector3D(-500.0f*mTransform->getScale().x(), 0.0f,  0.0f), QVector3D(1.0f, 0.0f,  0.0f), QVector2D(0.0f, 0.0f)}, // v0
        {QVector3D( 500.0f*mTransform->getScale().x(), 0.0f,  0.0f), QVector3D(1.0f, 0.0f,  0.0f), QVector2D(0.0f, 0.0f)}, // v1

        // Vertex data for Y-axix
        {QVector3D( 0.0f, -500.0f*mTransform->getScale().y(), 0.0f), QVector3D(0.0f, 1.0f,  0.0f), QVector2D( 0.0f, 0.0f)}, // v2
        {QVector3D( 0.0f,  500.0f*mTransform->getScale().x(), 0.0f), QVector3D(0.0f, 1.0f,  0.0f), QVector2D( 0.0f, 0.0f)}, // v3


        // Vertex data for Z-axix
        {QVector3D( 0.0f, 0.0f, -500.0f*mTransform->getScale().z()), QVector3D(0.0f, 0.0f,  1.0f), QVector2D(0.0f, 0.0f)}, // v3
        {QVector3D( 0.0f, 0.0f,  500.0f*mTransform->getScale().x()), QVector3D(0.0f, 0.0f,  1.0f), QVector2D(0.0f, 0.0f)} // v4
    };

    GLushort indices[] = {
        0, 1, 2, 3, 4, 5
    };

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO 0
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indices, GL_STATIC_DRAW);

    return 0;
}

void AxesGizmo::drawGeometry()
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    mMaterial->useMaterial();

    //refresh modelMatrix:
    //should not be neccecary since axes will not move:
    getMatrix();

    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
    mMaterial->setMVPMatrix(mMVPMatrix);

    // Offset for position
    // Positions are the first data, therefor offset is 0
    int offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getPositionAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<const void*>(offset));

    // Offset for vertex coordinates
    // before normals
    offset += sizeof(QVector3D);

    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getNormalAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<const void*>(offset));

    // Offset for normal coordinates
    // before UVs
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getTextureAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<const void*>(offset));

    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);

    // Write errors if any:
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        //qDebug() << "glGetError returns " << err;
    }
}

void AxesGizmo::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}


