#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
}
MyGLWidget::~MyGLWidget()
{}
void MyGLWidget::initializeGL()
{
     // 启用阴影平滑
    glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
     // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}
void MyGLWidget::paintGL()
{
    // 清除屏幕和深度缓存
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    //坐标转移
    glTranslatef(-1.5f,0.0f,-6.0f);
    //设置颜色
    glColor3f( 1.0, 1.0, 1.0 );
    //绘制一个正方形
    glBegin( GL_QUADS );
    glVertex3f( -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glEnd();
}
 // 重置OpenGL窗口大小
void MyGLWidget::resizeGL(int width, int height)
{
        // 防止窗口大小变为0
    if ( height == 0 )
    {
        height = 1;
    }
    // 重置当前的视口
    glViewport( 0, 0, (GLint)width, (GLint)height );
    // 选择投影矩阵
    glMatrixMode( GL_PROJECTION );
        // 重置投影矩阵
    glLoadIdentity();
    // 设置视口的大小
    //gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    // 选择模型观察矩阵
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
