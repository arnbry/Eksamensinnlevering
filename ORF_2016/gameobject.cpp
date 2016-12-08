#include "gameobject.h"

#include <QVector2D>
#include <QVector3D>

#include "vertexdata.h"

GameObject::GameObject(float xPos, float yPos, float zPos , QObject *parent) :mParent(nullptr), QObject(parent)
{
    initializeOpenGLFunctions();

    mTransform = new Transform(this);
    mTransform->setPosition(QVector3D(xPos, yPos, zPos));
}

GameObject::~GameObject()
{
    delete mTransform;
}


void GameObject::GOUpdate()
{
    //mScript->update();

        if (mScript != nullptr)
         {
             mScript->update();
         }
}

void GameObject::setParent(GameObject *parent)
{
    mParent = parent;

    //Do something to my own transform?
}

void GameObject::setViewMatrix(QMatrix4x4 viewMatrix)
{
    mViewMatrix = viewMatrix;
}

void GameObject::setprojectionMatrix(QMatrix4x4 projectionMatrix)
{
    mProjectionMatrix = projectionMatrix;
}

void GameObject::setScript(QString filepath)
{

    mInput = mInput->getInstance();
    mScript = new Scripting(this,mInput,filepath);
}



QMatrix4x4 GameObject::getMatrix()
{
    mModelMatrix.setToIdentity();
    mModelMatrix.translate(mTransform->getPosition());
    mModelMatrix.rotate(mTransform->getRotation().x(), 1.0, 0.0, 0.0);
    mModelMatrix.rotate(mTransform->getRotation().y(), 0.0, 1.0, 0.0);
    mModelMatrix.rotate(mTransform->getRotation().z(), 0.0, 0.0, 1.0);
    mModelMatrix.scale(mTransform->getScale());
    //mModelMatrix.translate(mTransform.mPosition);

    return mModelMatrix;
}

void GameObject::gameObjectDebug(float message)
{
    qDebug()<< message;
}

void GameObject::setPosition(float x,float y,float z)
{
    mTransform->setPosition(x,y,z);
}
void GameObject::translate(float x, float y, float z)
{

    mTransform->translate(x,y,z);
//    qDebug() << "hellleeeeeeeeeeeeeeeee";
}

void GameObject::scale(float x,float y,float z)
{
    mTransform->setScale(x,y,z);
}
