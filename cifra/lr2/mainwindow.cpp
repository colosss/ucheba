#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    openGLWidget = new myopenglwidget(this);
    setCentralWidget(openGLWidget);
    setWindowTitle("OpenGL Cone Example");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

// };
