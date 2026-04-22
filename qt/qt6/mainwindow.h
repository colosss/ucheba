#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "states.h"
#include "printjob.h"
#include "calculationfacade.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update();

private slots:
    void btnCalcPressed();
    void btnUndoPressed();

    void on_owner_textChanged(const QString &arg1);

private:
    PrintJob *processForm();
    void fillForm(PrintJob *job);
    void showCost(PrintJob *job);

    Ui::MainWindow *ui;
    states info;
};
#endif // MAINWINDOW_H
