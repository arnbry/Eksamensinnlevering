
#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditorWindow;
}
/**
 * @brief The EditorWindow class
 */
class EditorWindow : public QMainWindow
{

    Q_OBJECT

public:
    /**
     * @brief EditorWindow
     * @param parent
     */
    explicit EditorWindow(QWidget *parent = 0);


    ~EditorWindow();
    /**
     * @brief setColor
     */
    void setColor();

private slots:
    /**
     * @brief on_actionQuit_triggered
     */
    void on_actionQuit_triggered();
    /**
     * @brief on_actionLoad_Mesh_triggered
     */
    void on_actionLoad_Mesh_triggered();
    /**
     * @brief on_ColorButton_released
     */
    void on_ColorButton_released();

private:
    /**
     * @brief ui
     */
    Ui::EditorWindow *ui;

};

#endif // EDITORWINDOW_H
