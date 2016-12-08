#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>
#include <QMatrix4x4>
#include "transform.h"
#include "gameobject.h"
/**
 * @brief The Camera class
 */
class Camera : public GameObject
{
    //Q_OBJECT
public:
    /**
     * @brief mBackgroundColor
     */
    QVector4D mBackgroundColor ;
    /**
     * @brief mNearPlane
     */
    float mNearPlane;
    /**
     * @brief mFarPlane
     */
    float mFarPlane;
    /**
     * @brief mFieldOfView
     */
    float mFieldOfView;
    /**
     * @brief mHeight
     */
    int mHeight;
    /**
     * @brief mWidth
     */
    int mWidth;
    /**
     * @brief mAspectRatio
     */
    float mAspectRatio;

    /**
     * @brief mPerspective
     */
    QMatrix4x4 mPerspective;
    /**
     * @brief mViewMatrix
     */
    QMatrix4x4 mViewMatrix;
    /**
     * @brief Camera
     * @param height
     * @param width
     * @param nearPlane
     * @param farPlane
     * @param fov
     */
    Camera(int height = 800, int width = 1200, float nearPlane = 1.0f, float farPlane = 400.0f, float fov = 45.0f);
    /**
     * @brief rotate
     * @param angle
     * @param axis
     */
    void rotate(float angle, const QVector3D &axis);


    /**
     * @brief translate
     * @param x
     * @param y
     * @param z
     */
    void translate (float x, float y, float z);
    /**
     * @brief setAspectRatio
     * @param w
     * @param h
     * @param ortho
     */
    void setAspectRatio(int w, int h, bool ortho = false);
    /**
     * @brief setBackgroundColor
     * @param r
     * @param g
     * @param b
     * @param a
     */
    void setBackgroundColor(float r, float g, float b, float a);
    /**
     * @brief drawGeometry
     */
    void drawGeometry();
    /**
     * @brief initGeometry
     * @return
     */
    int initGeometry();

    //for compability with GameObject
    /**
     * @brief setMaterial
     * @param materialIn
     */
    void setMaterial(Material *materialIn){}
    /**
     * @brief setRendermode
     * @param mode
     */
    void setRendermode(int mode){}
    void GOUpdate(){}
};

#endif // CAMERA_H
