#include "myopenglwidget.h"

#include <QOpenGLFunctions>
#include <cmath>




myopenglwidget::myopenglwidget(QWidget *parent)
    :QOpenGLWidget(parent)
{

}

void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Темно-серый фон
    glEnable(GL_DEPTH_TEST); // Включаем тест глубины
}

void myopenglwidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // // gluPerspective(45.0, (double)w / h, 0.1, 100.0); // Настраиваем перспективу
    // glMatrixMode(GL_MODELVIEW);
}




void myopenglwidget::drawCone()
{
    // Рисуем конус в координатах от -1 до 1
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex3f(-0.5, -0.5, 0);
    glColor3f(0, 1, 0); glVertex3f(0.5, -0.5, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.5, 0);
    glEnd();
}

void myopenglwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Рисуем в нормализованных координатах (-1 до 1)
    drawCone();
}
