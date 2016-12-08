/*#include "assets.h"
#include "meshobject.h"

#include <QVector2D>
#include <QVector3D>
#include "vertexdata.h"

Assets::Assets(string modelPath, string audioPath)
{
    //meee = nullptr;
    wDir = QDir::currentPath().toStdString(); // set wDir as the current working directory.
    //initializeOpenGLFunctions();
    LoadMeshFolder(modelPath);
    LoadAudioFolder(audioPath);
    LoadTextureFolder("Assets/Textures");

    vector<string> names = GetMeshNames();

    bool foundY = false;
    for (int i = 0; i < names.size(); i++)
    {
        if (names[i] == "Yoshi5.obj")
            foundY = true;
    }

    if (foundY == true)
    {
        qDebug() << "trying to reimport Yoshi5.obj";
    }
}

void Assets::LoadMeshFolder(string path)
{
    vector<string> fileNames = FileNamesFromFolder(path);
    meshCount = fileNames.size();

    qDebug() << meshCount;
    if (meshCount < 1)
        qDebug() << "No files found / No folder found at" << path.c_str();

    qDebug() << "starting loading all mesh files";
    for(int i = 0; i < meshCount; i++)
    {
        std::string name = "/" + path + "/" + fileNames.at(i);
        QString qs = QString::fromStdString(wDir) + QString::fromStdString(name);
        qDebug()<<qs;
        MMesh *tempMesh = new MMesh();
        tempMesh->LoadFile(qs);
        tempMesh->name = fileNames.at(i);
        if (tempMesh->GetIndexes() > 0)
            mesh.push_back(tempMesh);
        else
            qDebug() << "Indexes was too low to be added";
    }
    qDebug() << "finish loading all mesh files";
}

void Assets::LoadAudioFolder(string path)
{
    vector<string> fileNames = FileNamesFromFolder(path);
    int soundCount = fileNames.size();

    qDebug() << soundCount;
    if (soundCount < 1)
        qDebug() << "No files found / No folder found at" << path.c_str();

    SoundManager::getInstance()->init();
    qDebug() << "starting loading all audio files";
    for(int i = 0; i < soundCount; i++)
    {
        string aName = path + "/" + fileNames.at(i);

        SoundSource* tempSound = SoundManager::getInstance()->createSource(
                    fileNames.at(i), Vector3(0.0f, 0.0f, 0.0f),
                    aName, false, 1.0f);
        tempSound->play();
        audio.push_back(tempSound);
    }
    qDebug() << "finish loading all audio files";
}

void Assets::LoadTextureFolder(string path)
{
    vector<string> fileNames = FileNamesFromFolder(path);
    int texCount = fileNames.size();

    for (int i = 0; i < texCount; i++)
    {
        string aName = path + "/" + fileNames.at(i);
        QString qName = QString::fromStdString(aName);
        qDebug() << aName.c_str();
        QImage img = QImage(qName).mirrored();
        if (!img.isNull()) // if image was loaded correctly
        {
            QOpenGLTexture *temp = new QOpenGLTexture(QImage(qName).mirrored());

            // Set nearest filtering mode for texture minification
            temp->setMinificationFilter(QOpenGLTexture::Nearest);

            // Set bilinear filtering mode for texture magnification
            temp->setMagnificationFilter(QOpenGLTexture::Linear);

            // Wrap texture coordinates by repeating
            // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
            temp->setWrapMode(QOpenGLTexture::Repeat);

            texture.push_back(temp);
        }
    }
    qDebug() << "finish loading all textures";
    qDebug() << "Textures saved" << texture.size();


}

vector<string> Assets::FileNamesFromFolder(string path)
{
    DIR *dir;
    dirent *pdir;
    vector<string> files;

    string folder;

    folder += wDir;
    folder += "/";
    folder += path;

    dir = opendir(folder.c_str());

    qDebug() << "FOLDER:" << dir;

    while(pdir = readdir(dir))
    {
        string name = pdir->d_name;
        qDebug() << "FILE" << name.c_str();
        if (name.length() > 2)
        files.push_back(name);
    }
    return files;
}

void Assets::initVertexBufferObjects()
{
    //initializeOpenGLFunctions();

    // Skal nå sende all vertex og color data til ett buffer
    //int lengde = m_nVertices * 8;//sizeof(Vertex)/sizeof(GLfloat);
    //float* bufferData = new float[lengde];
    //data(bufferData);
    //glGenBuffers(1, &mVertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, mNVertices*sizeof(VertexData),mVertices, GL_STATIC_DRAW);
}

MMesh *Assets::GetMeshByName(string name)
{
    for(int i = 0; i< meshCount; i++)
    {
        if (mesh[i]->name == name)
        {
            return mesh[i];
        }
    }
    return nullptr;
}

vector<string> Assets::GetMeshNames()
{
    vector<string> temp;
    for (int i = 0; i< meshCount; i++)
    {
        temp.push_back(mesh[i]->name);
    }
    return temp;
}*/
