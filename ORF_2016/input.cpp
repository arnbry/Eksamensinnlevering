#include "input.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QtWidgets>

Input* Input::mInstance = 0;

Input* Input::getInstance()
{
    if (!mInstance)
    {
        mInstance = new Input();
    }

    return mInstance;
}

Input::Input()
{
    mMousePos = QVector2D(0, 0);
    mMouseDeltaPos = QVector2D(0, 0);
    mLastMousePos = QVector2D(0, 0);

    mKeys = new InputKey[557];
    mMouseKeys = new MouseKey[53];

    keyboardHash = 557;
    hashedMouseButton = 53;
    cleanKeypresses();

    for (int i = 0; i < keyboardHash; i++)
        {
            mKeys[i].keyDown = false;
            mKeys[i].hold = false;
            mKeys[i].keyUp = false;
            mMouseDeltaPos = QVector2D(0, 0);
        }
}

bool Input::keyDown(Qt::Key key)
{
    int hashedKey = key % keyboardHash;
    if (mKeys[hashedKey].keyDown)
    {
        return true;
    }

    return false;
}

bool Input::keyHold(Qt::Key key)
{
    int hashedKey = key % keyboardHash;
    if (mKeys[hashedKey].hold)
    {
        return true;
    }

    return false;
}

bool Input::keyUp(Qt::Key key)
{
    int hashedKey = key % keyboardHash;
    if (mKeys[hashedKey].keyUp)
    {
        return true;
    }

    return false;
}

bool Input::mouseButtonDown(Qt::MouseButton mouseButton)
{
    int hashedKey = mouseButton % hashedMouseButton;
    if (mMouseKeys[hashedKey].mouseDown)
    {
        return true;
    }

    return false;
}

bool Input::mouseButtonHold(Qt::MouseButton mouseButton)
{
    int hashedKey = mouseButton % hashedMouseButton;
    if (mMouseKeys[hashedKey].mouseHold)
    {
        return true;
    }

    return false;
}

bool Input::mouseButtonUp(Qt::MouseButton mouseButton)
{
    int hashedKey = mouseButton % hashedMouseButton;
    if (mMouseKeys[hashedKey].mouseUp)
    {
        return true;
    }

    return false;
}

QVector2D Input::getMousePos()
{
    return mMousePos;
}

QVector2D Input::getMouseMovement()
{
    return mMouseDeltaPos;
}

void Input::keyPressUpdate(QKeyEvent *event)
{
    int hashedKey = event->key() % keyboardHash;
    qDebug() << "Pressed " << hashedKey << endl;
    if (!mKeys[hashedKey].hold)
    {
        mKeys[hashedKey].keyDown = true;
    }

    mKeys[hashedKey].hold = true;
}

void Input::keyReleaseUpdate(QKeyEvent *event)
{
    int hashedKey = event->key() % keyboardHash;
    qDebug() << "Released " << hashedKey << endl;
    if (mKeys[hashedKey].hold)
    {
        mKeys[hashedKey].keyUp = true;
    }

    mKeys[hashedKey].hold = false;
}

void Input::cleanKeypresses()
{
    for (int i = 0; i < keyboardHash; i++)
    {
        mKeys[i].keyDown = false;
        mKeys[i].keyUp = false;
        mMouseDeltaPos = QVector2D(0, 0);
    }

    for (int i = 0; i < hashedMouseButton; i++)
    {
        mMouseKeys[i].mouseDown = false;
        mMouseKeys[i].mouseUp = false;
    }


}

void Input::mouseMoveUpdate(QMouseEvent *event)
{
    mMousePos = QVector2D(event->localPos());

    mMouseDeltaPos = mMousePos - mLastMousePos;

    mLastMousePos = mMousePos;
}

void Input::mousePressUpdate(QMouseEvent *event)
{
    int hashedKey = event->button() % hashedMouseButton;
    if (!mMouseKeys[hashedKey].mouseHold)
    {
        mMouseKeys[hashedKey].mouseDown = true;
//        qDebug() << "Mouse " << event->button() << " down" << endl;
    }

    mMouseKeys[hashedKey].mouseHold = true;
}

void Input::mouseReleaseUpdate(QMouseEvent *event)
{
    int hashedKey = event->button() % hashedMouseButton;
//    qDebug() << "Mouse " << event->button() << " up" << endl;
    mMouseKeys[hashedKey].mouseUp = true;

    mMouseKeys[hashedKey].mouseHold = false;
}

