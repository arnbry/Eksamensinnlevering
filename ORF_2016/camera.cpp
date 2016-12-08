#include "camera.h"

Camera::Camera(int height, int width, float nearPlane, float farPlane, float fov)
    : mNearPlane(nearPlane), mFarPlane(farPlane), mFieldOfView(fov), mHeight(height), mWidth(width)
{
    mAspectRatio = static_cast<float>(mWidth)/static_cast<float>(mHeight ? mHeight : 1);
    mBackgroundColor = QVector4D(0.3f, 0.3f, 0.3f, 1.0f);
    mPerspective.setToIdentity();
    mPerspective.perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
    mViewMatrix.translate(-3.0, -2.0, -100.0);
}

void Camera::rotate(float angle, const QVector3D &axis)
{
    mViewMatrix.rotate(angle, axis);
}

//void Camera::rotateLock(float x, float y, float z)
//{
//    mTransform->rotate(x, y, z);
//    //mViewMatrix.rotate();
//}

void Camera::translate(float x, float y, float z)
{
    mViewMatrix.translate(x, y, z);
}

void Camera::setAspectRatio(int w, int h, bool ortho)
{
    mAspectRatio = static_cast<float>(w)/static_cast<float>(h ? h : 1);
    mPerspective.setToIdentity();

    if (ortho)
    {
        float scale{0.01f};
        mPerspective.ortho(-scale*w, scale*w, -scale*h , scale*h, mNearPlane, mFarPlane);
    }
    else
        mPerspective.perspective(mFieldOfView, mAspectRatio, mNearPlane, mFarPlane);
}

void Camera::setBackgroundColor(float r, float g, float b, float a)
{
    mBackgroundColor = QVector4D(r, g, b, a);
}

void Camera::drawGeometry()
{

}

int Camera::initGeometry()
{
    return 0;
}

