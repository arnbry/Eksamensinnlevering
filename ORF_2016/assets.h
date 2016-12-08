/*#ifndef ASSETS_H
#define ASSETS_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "transform.h"
#include "gameobject.h"
#include "vertexdata.h"

#include <fstream>
#include <dirent.h>

#include "mesh.h"

#include "modelloader.h"
#include <vector>
#include <iostream>

//OpenAL stuff
#include "SoundManager.h"
#include "SoundSource.h"
#include "Vector3.h"

#include <QOpenGLTexture>

using namespace std;


class Assets// : public GameObject
{
public:

    Assets(string modelPath, string audioPath);

    void initVertexBufferObjects();


    MMesh *GetMeshByName(string name);

    vector<string> GetMeshNames();

    vector<string> GetAudioNames();



private:
    QMatrix4x4 mModelMatrix;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    int mNVertices;
    VertexData* mVertices;

    void LoadMeshFolder(string path);
    void LoadAudioFolder(string path);
    void LoadTextureFolder(string path);

    vector<string> FileNamesFromFolder(string path);

    int vertsRemoveSoon;
    int indexesRemoveSoon;

    int meshCount;

    //Array of all meshes here
    vector<MMesh*> mesh;

public:
    //Textures
    vector<QOpenGLTexture*> texture;

    vector<SoundSource*> audio;

    string wDir;
};

#endif // ASSETS_H
