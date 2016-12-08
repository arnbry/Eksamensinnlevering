#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "input.h"
#include <vector>
#include "camera.h"
#include "axesgizmo.h"
#include "skybox.h"
#include "mesh.h"
#include "cube.h"
#include "circlesphere.h"
#include "shaderprogram.h"
#include "pointlight.h"
#include "scripting.h"
#include "vector3.h"
#include "SoundManager.h"
#include "SoundSource.h"

/**
 * @brief The GameEngine class
 */
class GameEngine : public QOpenGLWidget, protected QOpenGLFunctions
{

    Q_OBJECT

public:
    /**
     * @brief GameEngine
     * @param parent
     */
    explicit GameEngine(QWidget *parent = 0);
    ~GameEngine();

    /**
     * @brief init
     */
    void init();
    /**
     * @brief initMaterials
     */
    void initMaterials();

    /**
     * @brief cleanup
     */
    void cleanup();


    SoundSource* mExplosionSound;
    SoundSource* mLaserSound;
    SoundSource* mStereoSound;

    /**
     * @brief running
     * @return
     */
    bool running() { return mRunning; }
    /**
     * @brief quit
     */
    void quit() { mRunning = false; }

    /**
     * @brief loadMesh
     * @param fileName
     * @return
     */
    int loadMesh(QString fileName);


public slots:
    /**
     * @brief axisOnOff
     */
    void axisOnOff();
    /**
     * @brief wireFrameOnOff
     */
    void wireFrameOnOff();
    /**
     * @brief loadMesh
     */
    void loadMesh();
    /**
     * @brief setCameraColor
     */
    void setCameraColor();
    /**
     * @brief orthographicOnOff
     */
    void orthographicOnOff();


protected:
    //This is the "handleEvents" part:

    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief mouseMoveEvent
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief keyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief keyReleaseEvent
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    /**
     * @brief handleKeys
     */
    void handleKeys();
    /**
     * @brief timerEvent
     * @param e
     */
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
    /**
     * @brief initializeGL
     */
    void initializeGL() Q_DECL_OVERRIDE;
    /**
     * @brief resizeGL
     * @param w
     * @param h
     */
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    /**
     * @brief paintGL
     */
    void paintGL() Q_DECL_OVERRIDE;

private:

    /**
     * @brief mTimer
     */
    QBasicTimer mTimer;
    /**
     * @brief mMaterials
     */
    Material *mMaterials[4];
    /**
     * @brief mCamera
     */
    Camera *mCamera;
    /**
     * @brief viewMatrix
     */
    QMatrix4x4 viewMatrix;
    /**
     * @brief projectionMatrix
     */
    QMatrix4x4 projectionMatrix;

    /**
     * @brief noOfObjects
     */
    unsigned long noOfObjects = 55;
    /**
     * @brief mGeometry
     */
    std::vector<GameObject*> mGeometry;

    /**
     * @brief axes
     */
    GameObject *axes;
    /**
     * @brief skybox
     */
    GameObject *skybox;
    //dag sin oblig
    Mesh *mPlane;
    Mesh *mBall;
    /**
     * @brief loadedMesh
     */
    Mesh *Player;
    /**
     * @brief MonkeyScript
     */
    Scripting *MonkeyScript;
    /**
     * @brief CameraScript
     */
    Scripting *CameraScript;

    /**
     * @brief input
     */
    Input *input;

    //PointLight *mLight;

    /**
     * @brief mousePressPosition
     */
    QVector2D mousePressPosition;
    /**
     * @brief rotationAxis
     */
    QVector3D rotationAxis;
    /**
     * @brief angularSpeed
     */
    float angularSpeed;     //speed of rotation made by mouse
    /**
     * @brief rotation
     */
    QQuaternion rotation;
    /**
     * @brief fragmentShaderFileName
     */
    QString* fragmentShaderFileName;
    /**
     * @brief vertexShaderFileName
     */
    QString* vertexShaderFileName;
    /**
     * @brief mRunning
     */

    bool mRunning;

    /**
     * @brief axisOn
     */
    bool axisOn = false;
    /**
     * @brief wireFrame
     */
    bool wireFrame = false;
    /**
     * @brief ortho
     */
    bool ortho = false;



    int mouseXlast{};
    int mouseYlast{};
    /**
     * @brief cameraSpeed
     */
    float cameraSpeed = 0.2f;

    Cube*tempobj;


};

#endif // GAMEENGINE_H

/*
ModelLoader class is taken from/based on this article:
http://www.ics.com/blog/qt-and-opengl-loading-3d-model-open-asset-import-library-assimp
*/
