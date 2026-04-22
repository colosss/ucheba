#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>

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

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_con_1_released();

    void on_pushButton_con_2_released();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_hard_1_released();

    void on_pushButton_hard_2_released();

    void on_textBrowser_ishod_textChanged();

    void on_listWidget_ishod_itemSelectionChanged();


private:
    Ui::MainWindow *ui;

    QList<int> list_ishod;
    QList<int> list_modify;

    void show_element_by_id();
    void delete_element_by_id();
    void delete_element_by_mean();
    void add_element();
    void sum_elements();
    void sum_2_elemnts();
    void clear_m();
    void nu_null_list();
    void min_max();
    void refresh_modify_widget();


};
#endif // MAINWINDOW_H
