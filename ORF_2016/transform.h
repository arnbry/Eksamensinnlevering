#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include "gameobject.h"

class GameObject;
/**
 * @brief The Transform class
 */
class Transform
{
public:
    //Transform(){}
    /**
     * @brief Transform
     * @param owner
     */
    Transform(GameObject* owner);
    /**
     * @brief getPosition
     * @return
     */
    QVector3D getPosition();
    /**
     * @brief getRotation
     * @return
     */
    QVector3D getRotation();
    /**
     * @brief getScale
     * @return
     */
    QVector3D getScale();
    /**
     * @brief setPosition
     * @param x
     * @param y
     * @param z
     */
    void setPosition(float x, float y, float z);
    /**
     * @brief setPosition
     * @param pos
     */
    void setPosition(QVector3D pos) { mLocalPosition = pos; }
    /**
     * @brief setRotation
     * @param x
     * @param y
     * @param z
     */
    void setRotation(float x, float y, float z);
    /**
     * @brief setRotation
     * @param rot
     */
    void setRotation(QVector3D rot) { mLocalRotation = rot; }
    /**
     * @brief setScale
     * @param x
     * @param y
     * @param z
     */
    void setScale(float x, float y, float z);
    /**
     * @brief setScale
     * @param scale
     */
    void setScale(QVector3D scale) { mLocalScale = scale; }
    /**
     * @brief translate
     * @param x
     * @param y
     * @param z
     */
    void translate(float x, float y, float z);
    /**
     * @brief rotate
     * @param x
     * @param y
     * @param z
     */
    void rotate(float x, float y, float z);
    /**
     * @brief rotateAround
     * @param point
     * @param axis
     */
    void rotateAround(QVector3D point, QVector3D axis);

private:
    /**
     * @brief mGameObject
     */
    GameObject* mGameObject;
    /**
     * @brief mLocalPosition
     */
    QVector3D mLocalPosition;
    /**
     * @brief mLocalRotation
     */
    QVector3D mLocalRotation;
    /**
     * @brief mLocalScale
     */
    QVector3D mLocalScale;
};

#endif // TRANSFORM_H
