#include "boundingvolume.h"
#include "gameobject.h"

BoundingVolume::BoundingVolume()
{

}

int BoundingVolume::initGeometry(const VertexData *mVertexData, int triangles)
{
    //setting start values
    //If mesh is centered around origo, it could be set to 0.0f
    float xMax = mVertexData[0].position.x();
    float xMin = mVertexData[0].position.x();
    float yMax = mVertexData[0].position.y();
    float yMin = mVertexData[0].position.y();
    float zMax = mVertexData[0].position.z();
    float zMin = mVertexData[0].position.z();

    //finding all corners
    for (int counter = 1; counter < triangles; counter++)
    {
        if (xMax < mVertexData[counter].position.x())
            xMax = mVertexData[counter].position.x();
        if (xMin > mVertexData[counter].position.x())
            xMin = mVertexData[counter].position.x();
        if (yMax < mVertexData[counter].position.y())
            yMax = mVertexData[counter].position.y();
        if (yMin > mVertexData[counter].position.y())
            yMin = mVertexData[counter].position.y();
        if (zMax < mVertexData[counter].position.z())
            zMax = mVertexData[counter].position.z();
        if (zMin > mVertexData[counter].position.z())
            zMin = mVertexData[counter].position.z();

    }

//    qDebug() << "xMax, xMin: "<< xMax << ", " << xMin;
//    qDebug() << "yMax, yMin: "<< yMax << ", " << yMin;
//    qDebug() << "zMax, zMin: "<< zMax << ", " << zMin;


    QVector3D color(1.0f, 1.0f, 1.0f);


    //Format: Position, Normal, UV - normales used as color.
    VertexData vertices[] = {
        // Vertex data for top
        {QVector3D(xMax, yMax,  zMax), color, QVector2D(0.0f, 0.0f)},// v0
        {QVector3D( xMax, yMax,  zMin), color, QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(xMin,  yMax,  zMin), color, QVector2D(0.0f, 0.5f)},// v2
        {QVector3D( xMin,  yMax,  zMax), color, QVector2D(0.33f, 0.5f)},// v3

        // Vertex data for bottom
        {QVector3D(xMax, yMin,  zMax), color, QVector2D(0.0f, 0.0f)},// v0
        {QVector3D( xMax, yMin,  zMin), color, QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(xMin,  yMin,  zMin), color, QVector2D(0.0f, 0.5f)},// v2
        {QVector3D( xMin,  yMin,  zMax), color, QVector2D(0.33f, 0.5f)},// v3
};

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {0, 1, 2, 3, 0,     //upper square
                          4, 5, 6, 7, 4,        //lower square
                          5, 1, 2, 6, 7, 3 };     //the rest

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO 0
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 8*sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 16*sizeof(GLushort), indices, GL_STATIC_DRAW);

    return 0;
}

void BoundingVolume::drawGeometry(Material *mMaterial)
{
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    //mMaterial->useMaterial();

    //refresh modelMatrix:
    //getMatrix();

    //mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
    //mMaterial->setMVPMatrix(mMVPMatrix);

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

    // Draw mesh geometry using indices from VBO 1
    glDrawElements(GL_LINE_LOOP, 16, GL_UNSIGNED_SHORT, 0);

    //Write errors if any:
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        //qDebug() << "glGetError returns " << err;
    }

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
