#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QMatrix4x4>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram *program;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
    QVector3D cameraPosition;
    QVector3D cameraTarget;
    QVector3D cameraUp;

    void updateCamera(); // Новый метод для обновления камеры

    float rotationAngle;
    float rotationAngle_x;
    float rotationAngle_y;
    void setupShaders();
    void drawCube(const QVector3D &position, const QVector3D &color,
                  float diffuse, float specular, float shininess);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


};

#endif // MAINWINDOW_H
