#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_allow_clicked()
{
    QString l1=ui->line_1->text();
    QString l2=ui->line_2->text();
    bool ok1=false;
    bool ok2=false;
    double d_l1=l1.toDouble(&ok1);
    double d_l2=l2.toDouble(&ok2);
    double otv=0;
    if (!ok1 || !ok2){
        QMessageBox::warning(this, "Ошибка", "Введите числа в оба поля!");
        return;
    }
    if (ui->add->isChecked()) {
        otv = d_l1 + d_l2;
        ui->otv->setText(QString::number(otv));
    }


}
