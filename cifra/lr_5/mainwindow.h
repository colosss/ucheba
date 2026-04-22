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
    void changeSphereSize(float delta);
    void changeSphereTransparency(float delta);
    void changeSphereReflection(float delta);
    void toggleLightRotation();
    void setLightRotationSpeed(float speed);
    void changeSphereAlpha(float delta);        // Новая функция (scene transparency)

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void drawSphere(const QVector3D &position, const QVector3D &color,
    float diffuse, float specular, float shininess, float alpha);


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
    // Параметры сферы
    float sphereRadius;
    float sphereAlpha;
    float sphereDiffuse;
    float sphereSpecular;
    float sphereShininess;
    QVector3D sphereColor;
    QVector3D spherePosition;

    // Параметры освещения
    float lightRotationAngle;
    float lightRotationSpeed;
    bool isLightRotating;
    float lightOrbitRadius;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


};

#endif // MAINWINDOW_H
