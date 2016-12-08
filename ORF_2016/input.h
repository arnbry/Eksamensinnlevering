#ifndef INPUT_H
#define INPUT_H

#include <QOpenGLWidget>
#include <QDebug>
#include <QVector2D>

using namespace std;

struct InputKey
{
    bool keyDown;
    bool keyUp;
    bool hold;
};

struct MouseKey
{
    bool mouseDown;
    bool mouseUp;
    bool mouseHold;
};

class Input : public QObject
{
    Q_OBJECT
public slots:
    bool keyDown(Qt::Key key);

    bool keyHold(Qt::Key key);

    bool keyUp(Qt::Key key);
public:
    static Input* getInstance();

    Input();

    bool mouseButtonDown(Qt::MouseButton mouseButton);

    bool mouseButtonHold(Qt::MouseButton mouseButton);

    bool mouseButtonUp(Qt::MouseButton mouseButton);

    QVector2D getMousePos();

    QVector2D getMouseMovement();

    void keyPressUpdate(QKeyEvent *event);

    void keyReleaseUpdate(QKeyEvent *event);

    void cleanKeypresses();

    void mouseMoveUpdate(QMouseEvent *event);

    void mousePressUpdate(QMouseEvent *event);

    void mouseReleaseUpdate(QMouseEvent *event);


private:
    int keyboardHash;
    int hashedMouseButton;

    QVector2D mMousePos;

    QVector2D mMouseDeltaPos;

    QVector2D mLastMousePos;

    static Input* mInstance;

    InputKey* mKeys;

    MouseKey* mMouseKeys;
};

#endif // INPUT_H
