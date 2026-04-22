#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPixmap"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->chbox_chehol, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->chbox_naushniki, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->chbox_provod, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->chbox_strahovka, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->chbox_zarad, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->chbox_zh, &QCheckBox::checkStateChanged, this, &MainWindow::on_chbox_chehol_released);
    connect(ui->rbutton, &QCheckBox::released, this, &MainWindow::on_rbutton_released);

}

class Corzina
{
public:
    QString itog_string="";
    double_t itog_int=0;
    double_t itog_i=0;
    int8_t items=0;
    double_t iphone=0;
    Corzina(){
        iphone+=129000;
        itog_string+="Iphone 17 Pro Max 256Gb - 129000р";
        items=1;
    }
    void chehol(){
        itog_int+=3000;
        itog_string+= "\nЧехол - 3000р";
        items+=1;
    }
    void naushniki(){
        itog_int+=3000;
        itog_string+="\nНаушники - 3000р";
        items+=1;
    }
    void provod(){
        itog_int+=1500;
        itog_string+="\nПровод Type-C - 1500р";
        items+=1;
    }
    void strahovka(){
        itog_int+=1000;
        itog_string+="\nСтраховка - 1000р";
        items+=1;
    }
    void zarad(){
        itog_int+=1500;
        itog_string+="\nБлок питания - 1500р";
        items+=1;
    }
    void zh(){
        itog_int+=500;
        itog_string+="\nЗащитное стекло - 500р";
        items+=1;
    }
    void skidka(){
        itog_string+="\nСкидка - 10%";
        itog_i=itog_int;
        itog_int=itog_int*0.9;
    }


    // QString chehol = "\nЧехол - 3000р";
    // int64_t chehol_int=3000;
    // QString naushniki = "\nНаушники - 3000р";
    // int64_t naushniki_int = 3000;
    // QString provod = "\nПровод - 1500р";
    // int64_t provod_int=1500;
    // QString strahovka = "\nСтраховка - 1000р";
    // int64_t strahovka_int=1000;
    // QString zarad = "\nБлок питания - 1500р";
    // int64_t zarad_int = 1500;
    // QString zh = "\nЗащитное стекло - 500р";
    // int64_t zh_int = 500;

};

// void clear_otv()
// {
//     ui->otv->clear();

// }

MainWindow::~MainWindow()
{
    QPixmap pixmap("iphone17.jpg");
    ui->image_lable->setPixmap(pixmap);
    delete ui;
}

void MainWindow::on_rbutton_released()
{
    // QString otv="Iphone 17 Pro Max 256Gb - 129000р";
    // int64_t int_otv=0;
    Corzina corz;
    if (ui->chbox_chehol->isChecked()){
        corz.chehol();
    }
    if (ui->chbox_zh->isChecked()){
        corz.zh();
    }
    if (ui->chbox_provod->isChecked()){
        corz.provod();
    }
    if (ui->chbox_zarad->isChecked()){
        corz.zarad();
    }
    if (ui->chbox_naushniki->isChecked()){
        corz.naushniki();
    }
    if (ui->chbox_strahovka->isChecked()){
        corz.strahovka();
    }
    if(corz.items>=7){
        corz.skidka();
        ui->otv_coml->setText(QString::number(corz.itog_i, 'f', 2)+"р"+"\nСкидка -> "+QString::number(corz.itog_i*0.1, 'f', 2)+"р"+"\nС учетом скидки: "+QString::number(corz.itog_int, 'f',2)+"р");
    }
    else{
        ui->otv_coml->setText(QString::number(corz.itog_int, 'f', 2)+"р");
    }
    ui->spisok_vivod_lable->setText(corz.itog_string);

    ui->otv->setText(QString::number(corz.itog_int+corz.iphone, 'f', 2)+"р");
}



void MainWindow::on_chbox_chehol_released()
{
    ui->otv->clear();
    ui->spisok_vivod_lable->clear();
}

