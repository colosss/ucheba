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
    connect(ui->rb_obich, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_sroch, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_petg, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_petg_rapid_plus, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_pla, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_pla_plus, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
    connect(ui->rb_tpu, &QRadioButton::released, this, &MainWindow::on_rb_obich_released);
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

        if (ui->rb_pla->isChecked() or ui->rb_petg->isChecked()) itog+=0;
        else if (ui->rb_pla_plus->isChecked() or ui->rb_petg_rapid_plus->isChecked()) itog+=50;
        else if (ui->rb_tpu->isChecked()) itog+=150;

        if (ui->rb_obich->isChecked()) itog+=0;
        else if(ui->rb_sroch->isChecked())itog+=1000;

        itog+=time.toDouble()*0.12;
        itog+=ves.toDouble();


        ui->label_itog_otv->setText(QString::number(itog)+"р");
    }
}


void MainWindow::on_lineEdit_ves_textChanged(const QString &arg1)
{
    if (arg1.isEmpty()) ui->label_itog_otv->clear();
}


void MainWindow::on_rb_obich_released()
{
    ui->label_itog_otv->clear();
}

