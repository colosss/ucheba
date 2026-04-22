#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->allow, &QPushButton::released, this, &MainWindow::on_allow_released);
    connect(ui->line_1, &QLineEdit::textChanged, this, &MainWindow::on_line_1_textChanged);
    connect(ui->line_2, &QLineEdit::textChanged, this, &MainWindow::on_line_2_textChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_allow_released()
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
        ui->otv->clear();
        return;
    }
    if (ui->add->isChecked()) otv=d_l1+d_l2;
    else if(ui->minus->isChecked()) otv=d_l1-d_l2;
    else if(ui->multiply->isChecked()) otv=d_l1*d_l2;
    else if(ui->divine->isChecked()){
        if (d_l2==0){
            QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
            ui->otv->clear();
            return;
        }
        else{
            otv=d_l1/d_l2;
        }
    }
    else if(ui->dvr->isChecked()){
        if (d_l2==0){
            QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
            ui->otv->clear();
            return;
        }
        else{
            int cel=static_cast<int>(d_l1/d_l2);
            otv=cel;
        }
    }
    ui->otv->setText(QString::number(otv));
}


void MainWindow::on_line_1_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) ui->otv->clear();
}


void MainWindow::on_line_2_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) ui->otv->clear();
}

