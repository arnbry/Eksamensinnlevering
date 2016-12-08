#include "cube.h"

Cube::Cube(float xPos, float yPos, float zPos) : GameObject(xPos, yPos, zPos)
{
    initGeometry();
}

void Cube::drawGeometry()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    mMaterial->useMaterial();

    //refresh modelMatrix:
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

    // Draw cube geometry using indices from VBO 1
    if (!wireFrame)
        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    else
        glDrawElements(GL_LINES, 34, GL_UNSIGNED_SHORT, 0);

    //Write errors if any:
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        //qDebug() << "glGetError returns " << err;
    }

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Unbind shader
    glUseProgram(0);
}

int Cube::initGeometry()
{
    //For now hard coded as a cube:

    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    //qDebug() << "Init Geometry - Cube";
    //Format: Position, Normal, UV
    VertexData vertices[] = {
        // Vertex data for face 0 - front
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f, 0.0f,  1.0f), QVector2D(0.0f, 0.0f)},// v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.0f, 1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f, 0.0f,  1.0f), QVector2D(0.0f, 0.5f)},// v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.0f, 1.0f,  1.0f), QVector2D(0.33f, 0.5f)},// v3

        // Vertex data for face 1 - right
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(1.0f, 1.0f,  1.0f), QVector2D( 0.0f, 0.5f)},// v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(1.0f, 0.0f,  0.0f), QVector2D(0.33f, 0.5f)},// v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(1.0f, 0.0f,  1.0f), QVector2D(0.0f, 1.0f)}, // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(1.0f, 0.0f,  0.0f), QVector2D(0.33f, 1.0f)},  // v7

        // Vertex data for face 2 - back
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f,  -1.0f), QVector2D(0.66f, 0.5f)},// v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f,  -1.0f), QVector2D(1.0f, 0.5f)},// v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.0f, 1.0f,  -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f, 0.0f,  -1.0f), QVector2D(1.0f, 1.0f)},// v11

        // Vertex data for face 3 - left
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(-1.0f, 0.0f,  0.0f), QVector2D(0.66f, 0.0f)},// v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(-1.0f, 0.0f,  1.0f),QVector2D(1.0f, 0.0f)}, // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(-1.0f, 0.0f,  0.0f), QVector2D(0.66f, 0.5f)},// v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(-1.0f, 0.0f,  0.0f), QVector2D(1.0f, 0.5f)}, // v15

        // Vertex data for face 4 - bottom
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f), QVector2D(0.33f, 0.0f)},// v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f,  0.0f), QVector2D(0.66f, 0.0f)},// v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.0f, -1.0f,  0.0f),QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5 - top
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f, 1.0f,  0.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(1.0f, 1.0f,  0.0f), QVector2D(0.66f, 0.5f)},// v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f, 1.0f,  0.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.0f, 1.0f,  0.0f), QVector2D(0.66f, 1.0f)} // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO 0
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 24*sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34*sizeof(GLushort), indices, GL_STATIC_DRAW);

    return 0;
}

void Cube::setRendermode(int mode)
{
    if (mode == 1)
        wireFrame = true;
    else if (mode == 0)
        wireFrame = false;
}

void Cube::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}
