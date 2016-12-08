QT       += core gui widgets opengl
QT       += core qml



TARGET = ORF_2016
TEMPLATE = app


mac {
#    LIBS += -framework OpenAL
}


win32 {
    INCLUDEPATH += .\\include
    INCLUDEPATH += $(OPENAL_HOME)\\include\\AL
    LIBS *= $(OPENAL_HOME)\\libs\\Win32\\libOpenAL32.dll.a

    INCLUDEPATH += "C:\Users\Eier\Documents\ArnsteinQTobligs\assimp-3.3.1\include"
    LIBS += -L "C:\Users\Eier\Documents\ArnsteinQTobligs\assimp-3.3.1\lib\release" -lassimp

}
#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11


SOURCES += main.cpp \
    camera.cpp \
    gameobject.cpp\
    pointlight.cpp \
    gameengine.cpp \
    axesgizmo.cpp \
    shaderprogram.cpp \
    editorwindow.cpp \
    filehandler.cpp \
    soundmanager.cpp \
    soundsource.cpp \
    scripting.cpp \
    modelloader.cpp \
    mesh.cpp \
    assets.cpp \
    boundingvolume.cpp \
    circlesphere.cpp \
    cube.cpp \
    input.cpp \
    material.cpp \
    skybox.cpp \
    transform.cpp \
    vertexdata.cpp \
    scenenode.cpp \
    scenemanager.cpp \
    updateplayer.cpp

HEADERS += \
    camera.h \
    gameobject.h \
    pointlight.h \
    gameengine.h \
    axesgizmo.h \
    shaderprogram.h \
    editorwindow.h \
    filehandler.h \
    soundmanager.h \
    soundsource.h \
    scripting.h \
    modelloader.h \
    mesh.h \
    assets.h \
    boundingvolume.h \
    circlesphere.h \
    constants.h \
    cube.h \
    input.h \
    material.h \
    skybox.h \
    transform.h \
    vertexdata.h \
    scenenode.h \
    scenemanager.h \
    updateplayer.h \
    vec3.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    monkeycat.qrc

FORMS += \
    EditorWindow.ui
