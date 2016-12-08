#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "transform.h"
#include "material.h"
#include "boundingvolume.h"
#include "input.h"
#include "scripting.h"
class Transform;
class Input;
class Scripting;
/**
 * @brief The GameObject class
 */
class GameObject : public QObject,protected QOpenGLFunctions
{

    Q_OBJECT
public:


    /**
     * @brief GameObject
     * @param xPos
     * @param yPos
     * @param zPos
     * @param parent
     */
    GameObject(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0, QObject *parent = 0);
    /**
     * @brief ~GameObject
     */
    virtual ~GameObject();

    //virtual int initGeometry() = 0;

    /**
     * @brief drawGeometry
     */
    virtual void drawGeometry() = 0;
    /**
     * @brief setMaterial
     * @param materialIn
     */
    virtual void setMaterial(Material *materialIn) = 0;
    /**
     * @brief setRendermode
     * @param mode
     */
    virtual void setRendermode(int mode) = 0;

    void GOUpdate();

    //void GOUpdate();
    /**
     * @brief setViewMatrix
     * @param viewMatrix
     */
    void setViewMatrix(QMatrix4x4 viewMatrix);
    /**
     * @brief setprojectionMatrix
     * @param projectionMatrix
     */
    void setprojectionMatrix(QMatrix4x4 projectionMatrix);

    void setScript(QString filepath);

    /**
     * @brief getMatrix
     * @return
     */
    QMatrix4x4 getMatrix();

    //    void scale(float x, float y, float z);
    //    void rotate(float x, float y, float z);

    /**
     * @brief mTransform
     */
    Transform *mTransform;
    //Scripting *mScript;
    //Input *mInput;
    /**
     * @brief getParent
     * @return
     */
    GameObject* getParent() { return mParent; }
    /**
     * @brief setParent
     * @param parent
     */
    void setParent(GameObject *parent);
public slots:
    /**
     * @brief gameObjectDebug
     * @param message
     */
    void gameObjectDebug(float message);
    /**
     * @brief scale
     * @param x
     * @param y
     * @param z
     */
    void scale(float x, float y, float z);
    /**
     * @brief setPosition
     * @param x
     * @param y
     * @param z
     */
    void setPosition(float x, float y, float z);
    /**
     * @brief translate
     * @param x
     * @param y
     * @param z
     */
    void translate(float x, float y, float z);



protected:
    /**
     * @brief initGeometry
     * @return
     */
    virtual int initGeometry() = 0;
    /**
     * @brief mModelMatrix
     */
    QMatrix4x4 mModelMatrix;
    /**
     * @brief mViewMatrix
     */
    QMatrix4x4 mViewMatrix;
    /**
     * @brief mProjectionMatrix
     */
    QMatrix4x4 mProjectionMatrix;

    //VertexData* mVertices;



    /**
     * @brief mParent
     */
    GameObject* mParent;
    /**
     * @brief wireFrame
     */
    bool wireFrame = false;
    /**
     * @brief mBoundingVolume
     */
    BoundingVolume *mBoundingVolume;

    Scripting *mScript = nullptr;

    Input *mInput;

    //bool HaveScript;

};

#endif // GAMEOBJECT_H
