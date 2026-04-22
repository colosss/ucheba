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
#include <QKeyEvent>
#include <QTimerEvent>
#include <vector>

    class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    // Сфера
    void changeSphereSize(float delta);
    void changeSphereTransparency(float delta);
    void changeSphereReflection(float delta);
    void changeSphereAlpha(float delta);        // Новая функция (scene transparency)

    // Освещение / управление
    void toggleLightRotation();
    void setLightRotationSpeed(float speed);

protected:
    // OpenGL события
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    // Примитивы
    void drawSphere(const QVector3D &position, const QVector3D &color,
                    float diffuse, float specular, float shininess, float alpha);
    void drawCube(const QVector3D &position, const QVector3D &color,
                  float diffuse, float specular, float shininess);

    // Новые примитивы (тор и NURBS)
    void drawTorus(const QVector3D &position, const QVector3D &color,
                   float innerR, float outerR, int segments, int sides,
                   float diffuse, float specular, float shininess, float alpha);

    // Отрисовка NURBS-поверхности; ctrlPts/weights ожидаются в виде ctrlU * ctrlV
    void drawNurbsSurface(const QMatrix4x4 &transform,
                          const std::vector<QVector3D> &ctrlPts,
                          const std::vector<float> &weights,
                          int degU, int degV,
                          int resU, int resV,
                          const QVector3D &color,
                          float diffuse, float specular, float shininess, float alpha);

private:
    // Шейдерная программа и матрицы
    QOpenGLShaderProgram *program;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

    // Камера
    QVector3D cameraPosition;
    QVector3D cameraTarget;
    QVector3D cameraUp;
    void updateCamera();

    // Вращения/углы
    float rotationAngle;
    float rotationAngle_x;
    float rotationAngle_y;

    // Шейдеры
    void setupShaders();

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

    // ----------------- Новые поля для тора / NURBS / тумана -----------------
    // Тор
    bool showTorus;
    float torusInnerRadius;
    float torusOuterRadius;
    int torusSegments;
    int torusSides;

    // NURBS
    bool showNurbs;
    int nurbsCtrlU;
    int nurbsCtrlV;
    std::vector<QVector3D> nurbsControlPoints;
    std::vector<float> nurbsWeights;

    // Туман
    bool fogEnabled;
    QVector3D fogColor;
    float fogDensity; // используется для экспоненциального тумана

    // Прочие утилиты (если понадобятся, можно добавить публичные сеттеры)
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
};

#endif // MAINWINDOW_H
