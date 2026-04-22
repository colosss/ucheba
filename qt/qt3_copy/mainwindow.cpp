#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit_ves, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_ves_textChanged);
    connect(ui->lineEdit_time, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_ves_textChanged);
    connect(ui->pushButton_raschet, &QPushButton::released, this, &MainWindow::on_pushButton_raschet_released);

    // QString ves=ui->lineEdit_time->text();
    // QString time=ui->lineEdit_ves->text();
    // if (!ves.isEmpty() and !time.isEmpty()) ui->pushButton_raschet->setEnabled(true);
    // else ui->pushButton_raschet->setEnabled(false);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_raschet_released()
{
    QString ves=ui->lineEdit_ves->text();
    QString time=ui->lineEdit_time->text();
    if (ves.isEmpty() or time.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Введите числа в оба поля!");
        ui->label_itog_otv->clear();
        return;
    }
    else{
        double_t itog=0;
        QString type=ui->comboBox_type->currentText();
        // switch (type) {
        // case "PLA":
        //     itog+=0;
        // case "PLA PLUS":
        //     itog+=50;
        // case "PETG":
        //     itog+=0;
        // case "PETG RAPID PLUS":
        //     itog+=50;
        // case "TPU":
        //     itog+=150;
        //     break;
        // default:
        //     itog+=0;
        //     break;
        // }

        if (type=="PLA" or type=="PETG") itog+=0;
        else if (type=="PLA PLUS" or type=="PETG RAPID PLUS") itog+=50;
        else if (type=="TPU") itog+=150;
        itog+=time.toDouble()*0.12;
        itog+=ves.toDouble();


        ui->label_itog_otv->setText(QString::number(itog)+"р");
    }
}


void MainWindow::on_lineEdit_ves_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) ui->label_itog_otv->clear();
}

