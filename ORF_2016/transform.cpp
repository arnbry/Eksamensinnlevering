#include "transform.h"


Transform::Transform(GameObject* owner)
{
    mLocalPosition = QVector3D(0, 0, 0);
    mLocalRotation = QVector3D(0, 0, 0);
    mLocalScale = QVector3D(1, 1, 1);

    mGameObject = owner;
}

QVector3D Transform::getPosition()
{
    if (mGameObject->getParent())
    {
        QVector3D parentPos = mGameObject->getParent()->mTransform->getPosition();
        return mLocalPosition + parentPos;
    }

    return mLocalPosition;
}

QVector3D Transform::getRotation()
{
    if (mGameObject->getParent())
    {
        QVector3D parentRot = mGameObject->getParent()->mTransform->getRotation();
        return mLocalRotation + parentRot;
    }

    return mLocalRotation;
}

QVector3D Transform::getScale()
{
    if (mGameObject->getParent() != nullptr)
    {
        QVector3D parentScale = mGameObject->getParent()->mTransform->getScale();
        return mLocalScale + parentScale;
    }

    return mLocalScale;
}

void Transform::setPosition(float x, float y, float z)
{
    mLocalPosition = QVector3D(x, y, z);
}

void Transform::setRotation(float x, float y, float z)
{
    mLocalRotation = QVector3D(x, y, z);
}

void Transform::setScale(float x, float y, float z)
{
    mLocalScale = QVector3D(x, y, z);
}

void Transform::translate(float x, float y, float z)
{
    mLocalPosition = mLocalPosition + QVector3D(x, y, z);
}

void Transform::rotate(float x, float y, float z)
{
    mLocalRotation = mLocalRotation + QVector3D(x, y, z);
}
