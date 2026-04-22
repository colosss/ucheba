#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>
// #include <GL/gl.h>


class myopenglwidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit myopenglwidget(QWidget *parent  = nullptr);

    // myopenglwidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    void drawCone();
};

#endif // MYOPENGLWIDGET_H
