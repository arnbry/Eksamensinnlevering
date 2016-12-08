#include "editorwindow.h"
#include "ui_EditorWindow.h"

#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
}

EditorWindow::~EditorWindow()
{
    //ui->RenderWindow->cleanup();
    delete ui;
}

void EditorWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void EditorWindow::on_actionLoad_Mesh_triggered()
{
    qDebug() << "Open Mesh says EditorWindow!";
}

void EditorWindow::on_ColorButton_released()
{
    qDebug() << "Test pressed";
    ui->RenderWindow->setCameraColor();
}
