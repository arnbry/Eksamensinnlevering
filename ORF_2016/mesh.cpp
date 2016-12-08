#include "mesh.h"
#include "modelloader.h"
#include <array>

Mesh::Mesh(float xPos, float yPos, float zPos) : GameObject(xPos, yPos, zPos)
{
    mBoundingVolume = new BoundingVolume();
}

Mesh::~Mesh()
{
    delete mBoundingVolume;
}

int Mesh::initGeometry()
{
//    qDebug() << "Init Geometry - Mesh from file" << mFileName;

    ModelLoader model;
    bool mError = false;

    QVector<float> *aiVertices;
    QVector<float> *aiNormals;
    QVector<QVector<float> > *aiTextureUV;
    QVector<unsigned int> *aiIndices;

    if(!model.Load(mFileName, ModelLoader::PathType::RelativePath))
    {
        mError = true;
        qDebug() << "Mesh with name " << mFileName << " not loaded. Something is wrong!";
        return -1;
    }

    model.getBufferData(&aiVertices, &aiNormals, &aiIndices);
    model.getTextureData(&aiTextureUV, 0, 0);

    mNoOfTriangles = aiVertices->size()/3;
//    qDebug() << "Number of triangles" << mNoOfTriangles;

    //Format: Position, Normal, UV
    VertexData *vertices = new VertexData[mNoOfTriangles];

    for (int counter = 0; counter < mNoOfTriangles; counter++)
    {
        VertexData tempVertex;
        float a = aiVertices->at(counter*3);
        float b = aiVertices->at(counter*3+1);
        float c = aiVertices->at(counter*3+2);
        tempVertex.position = QVector3D(a, b, c);

        a = aiNormals->at(counter*3);
        b = aiNormals->at(counter*3+1);
        c = aiNormals->at(counter*3+2);
        tempVertex.normal = QVector3D(a, b, c);

        tempVertex.texCoord = QVector2D(0.0, 0.0);
        vertices[counter] = tempVertex;
    }

    mNoIndices = aiIndices->size();
    GLushort *indices = new GLushort[mNoIndices];
    for (int count = 0; count < mNoIndices; count ++)
    {
        indices[count] = aiIndices->at(count);
    }

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO 0
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mNoOfTriangles*sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNoIndices*sizeof(GLushort), indices, GL_STATIC_DRAW);

    mBoundingVolume->initGeometry(vertices, mNoOfTriangles);

    delete[] vertices;
    delete[] indices;
    return 0;
}

void Mesh::drawGeometry()
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

    // Draw mesh geometry using indices from VBO 1
    if (!wireFrame)
    {
        glDrawElements(GL_TRIANGLES, mNoIndices, GL_UNSIGNED_SHORT, 0);
        //glDrawElements(GL_LINES, mNoIndices, GL_UNSIGNED_SHORT, 0);
    }

    else
        glDrawElements(GL_LINES, mNoIndices, GL_UNSIGNED_SHORT, 0);

    //Write errors if any:
    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        //qDebug() << "glGetError returns " << err;
    }

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mBoundingVolume->drawGeometry(mMaterial);

    //Unbind shader
    glUseProgram(0);
}

void Mesh::setMeshName(QString nameOfMesh)
{
    mFileName = nameOfMesh;
}

void Mesh::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}

void Mesh::setRendermode(int mode)
{
    if (mode == 1)
        wireFrame = true;
    else if (mode == 0)
        wireFrame = false;
}
