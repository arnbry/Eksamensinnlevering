#include "material.h"
#include "constants.h"

#include <QFile>
#include <QDebug>
#include <QMatrix4x4>

Material::Material(int type) : QOpenGLFunctions(), texture(nullptr)
{
    // - read the fragmentshader and vertexshader filenames
    // They are included in the shaders.qrc file
    // (or use "fragmentShaderFileName = new QString("../ORF_2016/FlatColorF.glsl");
    // for regular path on harddrive)
    switch (type)
    {
    case 2:
    case 3:
    case UNLIT_COLOR:
        fragmentShaderFileName = new QString(":/FlatColorF.glsl");
        vertexShaderFileName = new QString(":/FlatColorV.glsl");
        initShader();
        break;
    case UNLIT_TEXTURE:
        fragmentShaderFileName = new QString(":/FlatTextureF.glsl");
        vertexShaderFileName = new QString(":/FlatTextureV.glsl");
        initShader();
        initTextures();
        break;
    }
}

void Material::initShader()
{
    initializeOpenGLFunctions();
    QString vertexCode;
    QString fragmentCode;
    QFile vertexShaderFile(*vertexShaderFileName);
    QFile fragmentShaderFile(*fragmentShaderFileName);

    if (!vertexShaderFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << *vertexShaderFileName << " could not be opened";
    }

    if (!fragmentShaderFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << *fragmentShaderFileName << " could not be opened";
    }

    QTextStream fileIn1(&vertexShaderFile);
    vertexCode = fileIn1.readAll();
    QTextStream fileIn2(&fragmentShaderFile);
    fragmentCode = fileIn2.readAll();
    mShaderFlat = new ShaderProgram();
    mShaderFlat->initShader(vertexCode, fragmentCode);

    /// - read attribute and uniform addresses from shaderprogram's GPU memory

    //glBindAttribLocation(mShaderFlat->getShaderId(), 2, "aTexcoord");

//    mPositionAttribute = 0;
//    mNormalAttribute = 1;
//    mTextureAttribute = 2;

    int i = 0;
    glGetProgramiv(mShaderFlat->getShaderId(), GL_ACTIVE_ATTRIBUTES, &i);
    //qDebug() << "shaderprogram" << " number of attributes = " << i;

    mPositionAttribute = mShaderFlat->getAttribLocation("aVertexPosition");
    glEnableVertexAttribArray(static_cast<GLuint>(mPositionAttribute));

    mNormalAttribute = mShaderFlat->getAttribLocation("aNormal");
    glEnableVertexAttribArray(static_cast<GLuint>(mNormalAttribute));

    mTextureAttribute = mShaderFlat->getAttribLocation("aTexcoord");
    glEnableVertexAttribArray(static_cast<GLuint>(mTextureAttribute));

    //qDebug() << "mTextureAttribute " << mTextureAttribute;

    mUniformMVPMatrix = mShaderFlat->getUniformLocation("uMVPMatrix");
}

void Material::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(Orf::filePath + "Galakse.png").mirrored(false, true));

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Material::useMaterial()
{
    mShaderFlat->useProgram();
    if (texture != nullptr)
        texture->bind();
}

GLint Material::getPositionAttribute()
{
    return mPositionAttribute;
}

GLint Material::getNormalAttribute()
{
    return mNormalAttribute;
}

GLint Material::getTextureAttribute()
{
    return mTextureAttribute;
}

void Material::setMVPMatrix(QMatrix4x4 mvpMatrix)
{
    mShaderFlat->setUniformMatrix(mUniformMVPMatrix, 1, GL_FALSE, mvpMatrix.constData());

}

GLint Material::getMVPMatrix()
{
    return mUniformMVPMatrix;
}

