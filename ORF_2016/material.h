#ifndef MATERIAL_H
#define MATERIAL_H

#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include "shaderprogram.h"
/**
 * @brief The Material class
 */
class Material : protected QOpenGLFunctions
{
public:
    /**
     * @brief Material
     * @param type
     */
    Material(int type);
    /**
     * @brief initShader
     */
    void initShader();
    /**
     * @brief initTextures
     */
    void initTextures();
    /**
     * @brief useMaterial
     */
    void useMaterial();
    /**
     * @brief getPositionAttribute
     * @return
     */
    GLint getPositionAttribute();
    /**
     * @brief getNormalAttribute
     * @return
     */
    GLint getNormalAttribute();
    /**
     * @brief getTextureAttribute
     * @return
     */
    GLint getTextureAttribute();
    /**
     * @brief setMVPMatrix
     * @param mvpMatrix
     */
    void setMVPMatrix(QMatrix4x4 mvpMatrix);
    /**
     * @brief getMVPMatrix
     * @return
     */
    GLint getMVPMatrix();

private:
    /**
     * @brief The Types enum
     */
    enum Types
    {
        UNLIT_COLOR,
        UNLIT_TEXTURE,
        LIT_COLOR,
        LIT_TEXTURE
    };

    //The start of compiling the shaders ourselvs:
    //ShaderProgram *mShaderLight;
    /**
     * @brief mShaderFlat
     */
    ShaderProgram *mShaderFlat;
    /**
     * @brief fragmentShaderFileName
     */
    QString* fragmentShaderFileName;
    /**
     * @brief vertexShaderFileName
     */
    QString* vertexShaderFileName;
    /**
     * @brief texture
     */
    QOpenGLTexture *texture;
    /**
     * @brief mPositionAttribute
     */
    GLint mPositionAttribute;
    /**
     * @brief mNormalAttribute
     */
    GLint mNormalAttribute;
    /**
     * @brief mTextureAttribute
     */
    GLint mTextureAttribute;
    /**
     * @brief mUniformMVPMatrix
     */
    GLint mUniformMVPMatrix;

    //GLint mUniformMVMatrix;
    //GLint mUniformPMatrix;
};

#endif // MATERIAL_H
