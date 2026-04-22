#include "mainwindow.h"

#include <QTimer>
#include <cmath>
#include <GL/glu.h>

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent), rotationAngle(0.0f)
{
    startTimer(16);
}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 1.0f, 1.0f, 0.5f);
    glEnable(GL_DEPTH_TEST);
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Простой способ без gluPerspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Вместо gluPerspective используем это:
    gluPerspective(45.0, (float)w/h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);



    // Рисуем разноцветный треугольник
    glBegin(GL_QUADS);
    // Грань 1 (verh)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);   // 1
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f); // 2
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);  // 3
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f); //4

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);  //5
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f); // 6
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);  // 7
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);//8

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f); //    9
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);  //  10
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);  //  11
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f); //  12

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f); //    13
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);  //  14
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);  //  15
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f); //  16

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f); //    17
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);  //  18
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);  //  19
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); //  20

    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glVertex3f(-1.0f, -1.0f, -1.0f); //    21
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);  //  22
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);  //  23
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f); //  24

    // // Грань 2 (правая)
    // glColor3f(1.0f, 0.0f, 0.0f);    // Красный
    // glVertex3f(0.0f, 1.0f, 0.0f);   // Верхушка
    // glColor3f(0.0f, 1.0f, 0.0f);    // Зеленый
    // glVertex3f(1.0f, -1.0f, 1.0f);  // Передний-правый
    // glColor3f(0.0f, 0.0f, 1.0f);    // Синий
    // glVertex3f(1.0f, -1.0f, -1.0f); // Задний-правый

    // // Грань 3 (задняя)
    // glColor3f(1.0f, 0.0f, 0.0f);    // Красный
    // glVertex3f(0.0f, 1.0f, 0.0f);   // Верхушка
    // glColor3f(0.0f, 1.0f, 0.0f);    // Зеленый
    // glVertex3f(1.0f, -1.0f, -1.0f); // Задний-правый
    // glColor3f(0.0f, 0.0f, 1.0f);    // Синий
    // glVertex3f(-1.0f, -1.0f, -1.0f);// Задний-левый

    // // Грань 4 (левая)
    // glColor3f(1.0f, 0.0f, 0.0f);    // Красный
    // glVertex3f(0.0f, 1.0f, 0.0f);   // Верхушка
    // glColor3f(0.0f, 1.0f, 0.0f);    // Зеленый
    // glVertex3f(-1.0f, -1.0f, -1.0f);// Задний-левый
    // glColor3f(0.0f, 0.0f, 1.0f);    // Синий
    // glVertex3f(-1.0f, -1.0f, 1.0f); // Передний-левый
    glEnd();

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    rotationAngle += 1.0f;
    if(rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    update();
}
