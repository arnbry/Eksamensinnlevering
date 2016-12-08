#include "circlesphere.h"
#include <cmath>

CircleSphere::CircleSphere(int resolution, float xPos, float yPos, float zPos) : GameObject(xPos, yPos, zPos)
{
    setResolution(resolution);
    initGeometry();
}

int CircleSphere::initGeometry()
{
    float *x = new float[mVertexPrCircle]{};
    float *y = new float[mVertexPrCircle]{};

    double angle{};

    for(int i = 0; i < mVertexPrCircle; i++)
    {
        angle = 2 * 3.14 * i / mVertexPrCircle;
        x[i] = cos(angle)*mRadius;
        y[i] = sin(angle)*mRadius;
        //gl.glVertex2d(x,y);
    }

    //Format: Position, Normal, UV
    VertexData *vertices = new VertexData[mVertexPrCircle*3];

    // Vertex data for circle in xy-plane
    for (int i = 0; i < mVertexPrCircle; i++)
    {
        VertexData temp{};
        temp.position = QVector3D(x[i], y[i],  0.0f);
        temp.normal = mColor;
        temp.texCoord = QVector2D(0.0f, 0.0f);
        vertices[i] = temp;
    }

    // Vertex data for circle in xz-plane
    for (int i = 0; i < mVertexPrCircle; i++)
    {
        VertexData temp;
        temp.position = QVector3D(x[i], 0.0f, y[i]);
        temp.normal = mColor;
        temp.texCoord = QVector2D(0.0f, 0.0f);
        vertices[mVertexPrCircle + i] = temp;
    }

    // Vertex data for circle in yz-plane
    for (int i = 0; i < mVertexPrCircle; i++)
    {
        VertexData temp;
        temp.position = QVector3D(0.0f, y[i], x[i]);
        temp.normal = mColor;
        temp.texCoord = QVector2D(0.0f, 0.0f);
        vertices[(mVertexPrCircle * 2) + i] = temp;
    }

    //empty vertecies that has to be drawn:
    //this is because we use glDrawElements(GL_LINE_STRIP ....
    //for the 3. circle to begin correct, we draw on top of first circle
    //until we get to the crossing point
    int empty = ((mVertexPrCircle / 8) - 1) * 2 + 1;

    //if mVertexPrCircle == 4, empty becomes -1
    //so we correct that.
    if (empty < 0)
        empty = 0;

    // 3 circles + 3 extra to end each circle
    // + empty drawings to start 3. circle correct
    mNoIndices = mVertexPrCircle*3 + 3 + empty;
    GLushort *indices = new GLushort[mNoIndices];

    //trying to make indecies for all 3 circles:
    int tempIndex{};

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i< mVertexPrCircle; i++)
        {
            int temp = i + (mVertexPrCircle * (j));
            indices[tempIndex] = temp;
            tempIndex++;
        }
        //extra to end circle
        indices[tempIndex] = mVertexPrCircle * (j);

        //if j == 1 we are to start last circle
        //then we have to draw some redundant lines to
        //start last circle correct:
        if(j == 1)
        {
            for (int e = 1; e <= empty; e++)
            {
                tempIndex++;
                indices[tempIndex] = mVertexPrCircle + e;
            }
        }
        tempIndex++;
    }

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, (mVertexPrCircle*3*sizeof(VertexData)), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNoIndices*sizeof(GLushort), indices, GL_STATIC_DRAW);

    //clean up arrays we have created
    delete[] x;
    delete[] y;
    delete[] vertices;
    delete[] indices;

    return 0;
}

void CircleSphere::drawGeometry()
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

    glDrawElements(GL_LINE_STRIP, mNoIndices, GL_UNSIGNED_SHORT, 0);

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

void CircleSphere::setRendermode(int mode)
{
    if (mode == 1)
        wireFrame = true;
    else if (mode == 0)
        wireFrame = false;
}

void CircleSphere::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}

void CircleSphere::setResolution(int resolution)
{
    //can not have <= 0 in resolution
    if (resolution <= 0)
        resolution = 1;

    int temp{2};
    //calculate vertecies
    //1 = 4 vertecies, 2 = 8 vertecies, 3 = 16, etc.
    //has to be 4, 8, 16, 32, etc. for initGeometry to be correct.
    for (int i = 1; i <= resolution; i++)
    {
        temp = temp * 2;
    }

    mVertexPrCircle = temp;
}
