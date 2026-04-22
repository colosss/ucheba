#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions> // Для доступа к функциям OpenGL
#include <QOpenGLFunctions_1_1>

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions_1_1
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *event) override;
private:
    float rotationAngle;
};

#endif // MAINWINDOW_H
