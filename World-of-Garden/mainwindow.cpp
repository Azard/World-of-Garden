#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mygl = new MyGLWidget();


    fullscreen = true;
    setGeometry(100,100,1000,768);
    setWindowTitle(tr("NeHe's OpenGL Framework"));
    setCentralWidget(mygl);
}
MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {
    case Qt::Key_Escape:
        close();
        break;
    }
}
