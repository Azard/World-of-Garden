#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>
#include "myglwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool fullscreen;
    void keyPressEvent( QKeyEvent *e );

private:
    MyGLWidget *mygl;
};
#endif // MAINWINDOW_H
