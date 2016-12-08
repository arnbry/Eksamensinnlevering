#include "gameengine.h"
#include "constants.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QtWidgets>
#include <QColorDialog>

#include <cmath>

GameEngine::GameEngine(QWidget *parent) : QOpenGLWidget(parent)
{
    //mGameEnginePointer = this;
    //hei
}

GameEngine::~GameEngine()
{
    mRunning = false;
    mTimer.stop();
    cleanup();
}

void GameEngine::init()
{

    //makes the soundmanager
        //it is a Singleton
        SoundManager::getInstance()->init();






        //loads the sounds
        mExplosionSound = SoundManager::getInstance()->createSource(
                    "Explosion", QVector3D(-10.0f, 0.0f, 0.0f),
                    "bentzexplosion.wav", false, 1.0f);
        mLaserSound = SoundManager::getInstance()->createSource(
                    "Laser", QVector3D(20.0f, 0.0f, 0.0f),
                    "laser.wav", false, 1.0f);

        mStereoSound = SoundManager::getInstance()->createSource(
                    "Stereo", QVector3D(0.0f, 0.0f, 0.0f),
                    "happyhappy.wav", false, 1.0f);



        //placing the listener:
        QVector3D pos(0.0f, 0.0f, 1.0f);
        QVector3D vel(0.0f, 0.0f, 0.0f);
        QVector3D dir(0.0f, 0.0f, -1.0f);
        QVector3D up(0.0f, 1.0f, 0.0f);

        //set the listener position
       SoundManager::getInstance()->updateListener(pos, vel, dir, up);

       mStereoSound->play();

        //vector for source placement
       // Vector3 sourceVec3;

    mRunning = true;


    initializeOpenGLFunctions();

    //Must set this to get MouseMoveEvents without pressing a mouse key
    //this->setMouseTracking(true);

    // Enable depth buffer - must be done in GameEngine
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling - must be done in GameEngine
    glEnable(GL_CULL_FACE);

    initMaterials();

    mCamera = new Camera();
    mCamera->mTransform->setPosition(-3.0f, -2.0f, -20.0f);
    mCamera->setBackgroundColor(0.4f, 0.4f, 0.4f, 1.0f);

    glClearColor(mCamera->mBackgroundColor.x(),
                 mCamera->mBackgroundColor.y(),
                 mCamera->mBackgroundColor.z(),
                 mCamera->mBackgroundColor.w());

    //Quick hack to make lots of cubes:


    double squareRoot = sqrt(noOfObjects);

    GameObject *tempGeometry;
    for (unsigned long noOfCubesX = 0; noOfCubesX < squareRoot; noOfCubesX++)
    {
        for (unsigned long noOfCubesZ = 0; noOfCubesZ < squareRoot; noOfCubesZ++)
        {

//            tempGeometry = new Cube((-17.5f+noOfCubesX*5.0f), (20.0f+noOfCubesZ*5.0f), 0.0f);
//            tempGeometry->setMaterial(mMaterials[0]);
//            mGeometry.push_back(tempGeometry);
            //tempGeometry->setScript(":/monkey.js");

        }
    }

    /*
    Quick hack to make lots of ape heads:
        Mesh *tempGeometry;
        for (unsigned long noOfCubesX = 0; noOfCubesX < squareRoot; noOfCubesX++)
        {
            for (unsigned long noOfCubesZ = 0; noOfCubesZ < squareRoot; noOfCubesZ++)
            {
                tempGeometry = new Mesh((-5.0f+noOfCubesX*3.0f), 0.0f, (0.0f+noOfCubesZ*3.0f));
                tempGeometry->setMeshName("../ORF_2016/meshes/suzanne.obj.txt");
                tempGeometry->initGeometry();
                tempGeometry->setMaterial(mMaterials[0]);
                mGeometry.push_back(tempGeometry);
            }
        }
    */

    //circle-test:
//    CircleSphere *tempCircle = new CircleSphere(3, -2.0f, 3.0f, -3.0f);
//    tempCircle->setMaterial(mMaterials[0]);
//    mGeometry.push_back(tempCircle);

    axes = new AxesGizmo();
    axes->setMaterial(mMaterials[0]);

    skybox = new SkyBox();
    skybox->setMaterial(mMaterials[1]);
    skybox->mTransform->setScale(70.0f, 70.0f, 70.0f);
    mGeometry.push_back(skybox);
    input = new Input();


//    mPlane = new Mesh();
//    mPlane->setMeshName((Orf::filePath + "Plane.obj"));
//    mPlane->initGeometry();
//    mPlane->mTransform->setScale(10.0f, 10.0f, 10.0f);
//    mPlane->mTransform->setRotation(0.0f, 45.0f, 0.0f);
//    mPlane->setMaterial(mMaterials[0]);
//    mGeometry.push_back(mPlane);

//    mBall = new Mesh();
//    mBall->setMeshName((Orf::filePath + "Ball.obj"));
//    mBall->initGeometry();
//    mBall->mTransform->setScale(1.0f, 1.0f, 1.0f);
//    mBall->mTransform->setRotation(0.0f, 45.0f, 0.0f);
//    mBall->setMaterial(mMaterials[0]);
//    mGeometry.push_back(mBall);
    //set position of skybox to that of camera
    //skybox->setParent(mCamera);
    //does not work now, and would cause rotations with camera

    //manually loads a mesh
    Player = new Mesh(8.0f);
    Player->setMeshName((Orf::filePath + "suzanne.obj.txt"));
    Player->initGeometry();
    Player->mTransform->setScale(2.0f, 2.0f, 2.0f);
    Player->mTransform->setRotation(0.0f, 0.0f, 0.0f);
    Player->setMaterial(mMaterials[0]);
    mGeometry.push_back(Player);
    Player->setParent(mCamera);








    CameraScript = new Scripting(mCamera,input,":/camera.js");
    // Starts the Game Loop
    // Use QBasicTimer because its faster than QTimer
    mTimer.start(16, this);
}

void GameEngine::loadMesh()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    Mesh *tempGeometry = new Mesh(30.0f, 5.0f, 0.0f);
    tempGeometry->setMeshName(fileName);

    if (!tempGeometry->initGeometry())
    {
        tempGeometry->setMaterial(mMaterials[0]);
        mGeometry.push_back(tempGeometry);
    }
    else
        qDebug() << "Mesh" << fileName << "not loaded!!!";
}

void GameEngine::setCameraColor()
{
    QColor color = QColor(static_cast<int>(mCamera->mBackgroundColor.x()*255),
                          static_cast<int>(mCamera->mBackgroundColor.y()*255),
                          static_cast<int>(mCamera->mBackgroundColor.z()*255),
                          static_cast<int>(mCamera->mBackgroundColor.w()*255));

    QString title = QString("Select Background color");
    color = QColorDialog::getColor(color, this, title);

    if (color.isValid())
    {
        mCamera->setBackgroundColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());

        glClearColor(mCamera->mBackgroundColor.x(),
                     mCamera->mBackgroundColor.y(),
                     mCamera->mBackgroundColor.z(),
                     mCamera->mBackgroundColor.w());
    }
}

void GameEngine::initMaterials()
{
    //Makes 4 default materials
    //0. UnlitColors 1. LitColors 2.UnlitTexture 3. LitTexture
    //Only UnlitColor is implemented for now

    for (int no = 0; no < 4; no++)
    {
        mMaterials[no] = new Material(no);
    }

}

void GameEngine::cleanup()
{
    //Cleanup what we made in init():
    //    qDebug() << "Cleanup!";
    //    qDebug() << "Deleting" << mGeometry.size() << "objects";
    //Delete what we made in init()
    for (unsigned long noOfObjects = 0; noOfObjects < mGeometry.size(); ++noOfObjects)
    {
        delete mGeometry.at(noOfObjects);

        //The mGeometry vector deletes itself when going out of scope
    }
    mGeometry.clear();
    //    qDebug() << "mGeometry is now " << mGeometry.size() << "objects";

    if (axes)
    {
        delete axes;
        axes = nullptr;
        //        qDebug() << "Axes deleted";
    }
    for (int no = 0; no < 4; no++)
    {
        delete mMaterials[no];
        mMaterials[no] = nullptr;
        //        qDebug() << "Material" << no << "deleted";
    }

    if(mCamera)
    {
        delete mCamera;
        mCamera = nullptr;
        //        qDebug() << "Camera deleted";
    }
}

void GameEngine::mousePressEvent(QMouseEvent *event)
{
    input->mousePressUpdate(event);

}

void GameEngine::mouseReleaseEvent(QMouseEvent *event)
{
    input->mouseReleaseUpdate(event);
}

void GameEngine::mouseMoveEvent(QMouseEvent *event)
{
    input->mouseMoveUpdate(event);


    //input->event(event,mCamera);

    //    qDebug() << QString::number(event->pos().x());
    //    qDebug() << QString::number(event->pos().y());

    //using mouseXYlast as deltaXY so we don't need extra variables
    mouseXlast = event->pos().x() - mouseXlast;
    mouseYlast = event->pos().y() - mouseYlast;

    //if delta is to big the movement will be jerky
    //Happens if mouse is moved much between presses.
    if (mouseXlast > 40 || mouseYlast > 40 || mouseXlast < -40 || mouseYlast < -40)
    {
        mouseXlast = 0;
        mouseYlast = 0;
    }

    //qDebug() << "dX: "<< mouseXlast << ", dY: "<< mouseYlast;
    mCamera->rotate(cameraSpeed*mouseXlast, QVector3D(0.0,1.0,0.0));
    mCamera->rotate(cameraSpeed*mouseYlast, QVector3D(1.0,0.0,0.0));

    mouseXlast = event->pos().x();
    mouseYlast = event->pos().y();

}

void GameEngine::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        input->keyPressUpdate(event);
    }

}

void GameEngine::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
        {
            input->keyReleaseUpdate(event);

        }
}

void GameEngine::handleKeys()
{

//    if(input->keyHold(Qt::Key_Left))
//    {




//        mCamera->translate(0.2f, 0.0, 0.0);
//    }
//    if(input->keyHold(Qt::Key_Right))
//    {
//         mCamera->translate(-0.2f, 0.0, 0.0);
//    }
//    if(input->keyHold(Qt::Key_Up))
//    {
//        mCamera->translate(0.0, 0.0, 0.2f);
//    }
//    if(input->keyHold(Qt::Key_Down))
//    {
//         mCamera->translate(0.0, 0.0, -0.2f);
//    }
    if(input->keyHold(Qt::Key_A))
    {
        Player->translate(-0.5f, 0.0, 0.0);

    }
    if(input->keyHold(Qt::Key_A))
    {
        mCamera->translate(0.5f, 0.0, 0.0);

    }
    if(input->keyHold(Qt::Key_D))
    {
        Player->translate(0.5f, 0.0, 0.0);

    }
    if(input->keyHold(Qt::Key_D))
    {
        mCamera->translate(-0.5f, 0.0, 0.0);

    }
    if(input->keyHold(Qt::Key_S))
    {
        Player->translate(0.0, 0.0f, 0.5);
    }
    if(input->keyHold(Qt::Key_S))
    {
        mCamera->translate(0.0, 0.0f, -0.5);
    }
    if(input->keyHold(Qt::Key_W))
    {
        Player->translate(0.0, 0.0f, -0.5);
    }
    if(input->keyHold(Qt::Key_W))
    {
        mCamera->translate(0.0, 0.0f, 0.5);
    }

    if(input->keyDown(Qt::Key_Space))
    {
//            //bruker denne som ammo
//        tempobj = new Cube(loadedMesh->mTransform->getPosition().x(),loadedMesh->mTransform->getPosition().y(),loadedMesh->mTransform->getPosition().z());

//        tempobj->initGeometry();
//        tempobj->setMaterial(mMaterials[0]);
//        //script på ammo
//        tempobj->setScript(":/monkey.js");
// //       tempobj->drawGeometry();
//        //MonkeyScript = new Scripting(tempobj,input,":/monkey.js");


//        mGeometry.push_back(tempobj);
//        mLaserSound->play();


    }



}

void GameEngine::timerEvent(QTimerEvent *e)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.98;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, static_cast<float>(angularSpeed));// * rotation;
    }

    handleKeys();

    //MonkeyScript->update();
   // CameraScript->update();

    // Request an update for the QOpenGL widget


    GameObject *tempGeometry;



    for (unsigned long noOfObjects = 0; noOfObjects < mGeometry.size(); ++noOfObjects)
    {
        //qDebug() << noOfObjects;

        tempGeometry = mGeometry.at(noOfObjects);
        tempGeometry->GOUpdate();

    }

    input->cleanKeypresses();



    update();




}

//This function is called from the Qt framework
void GameEngine::initializeGL()
{
    initializeOpenGLFunctions();
    init();
}

void GameEngine::resizeGL(int w, int h)
{
    //This function is called from Qt
    //Maybe before the camera is made.

    //Maybe needed for retina displays
    //    const qreal retinaScale = devicePixelRatio();
    //    qDebug() << "Retina " << retinaScale;

    mCamera->setAspectRatio(w, h);
}

void GameEngine::paintGL()
{

    //paintGL is the Qt function called from the internal Qt loop

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(mCamera->mBackgroundColor.x(),
                 mCamera->mBackgroundColor.y(),
                 mCamera->mBackgroundColor.z(),
                 mCamera->mBackgroundColor.w());

    // Calculate view transformation
    if (!mCamera)
        qDebug() << "Rendering without camera!";
    //mCamera->rotate(angularSpeed, rotationAxis);

    // cameras viewMatrix - same for all objects
    viewMatrix = mCamera->mViewMatrix;
    // cameras projectionMatrix - same for all objects
    projectionMatrix = mCamera->mPerspective;

    //set position of skybox to that of camera
    skybox->mTransform->setPosition(mCamera->mTransform->getPosition());


    //Draw all geometry in mGeometry vector:
    GameObject *tempGeometry;

    for (unsigned long noOfObjects = 0; noOfObjects < mGeometry.size(); ++noOfObjects)
    {
        tempGeometry = mGeometry.at(noOfObjects);
        tempGeometry->setViewMatrix(viewMatrix);
        tempGeometry->setprojectionMatrix(projectionMatrix);
        tempGeometry->drawGeometry();
    }

    //    loadedMesh->setViewMatrix(viewMatrix);
    //    loadedMesh->setprojectionMatrix(projectionMatrix);
    //    loadedMesh->drawGeometry();

    //if editor button is pressed
    if (axisOn)
    {
        //Axes ******************************************:
        axes->setViewMatrix(viewMatrix);
        axes->setprojectionMatrix(projectionMatrix);
        axes->drawGeometry();
    }
}

void GameEngine::axisOnOff()
{
    //    qDebug() << "Axis on/off";
    axisOn = !axisOn;
}

void GameEngine::orthographicOnOff()
{
    ortho = !ortho;
    if (ortho)
        mCamera->setAspectRatio(1280, 720, true);
    else
        mCamera->setAspectRatio(1280, 720);
}

void GameEngine::wireFrameOnOff()
{
    //    qDebug() << "Wireframe on/off";
    wireFrame = !wireFrame;
    GameObject *tempGeometry;
    for (unsigned long noOfObjects = 0; noOfObjects < mGeometry.size(); ++noOfObjects)
    {
        tempGeometry = mGeometry.at(noOfObjects);
        tempGeometry->setRendermode(wireFrame);
    }
}
