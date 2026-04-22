#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myopenglwidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
// public:
//     explicit MainWindow(QWidget *parent = nullptr);

private:
    myopenglwidget *openGLWidget;
};
#endif // MAINWINDOW_H
