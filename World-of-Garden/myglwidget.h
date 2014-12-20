#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include <QOpenGLWidget>
class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
protected:

    void initializeGL();

    void paintGL();

    void resizeGL( int width, int height );
};
#endif // MYGLWIDGET_H
