#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnUndo->setEnabled(false);

    connect(&info, SIGNAL(notifyObservers()), this, SLOT(update()));
    connect(ui->btnCalc, SIGNAL(pressed()), this, SLOT(btnCalcPressed()));
    connect(ui->btnUndo, SIGNAL(pressed()), this, SLOT(btnUndoPressed()));
    connect(ui->copies, &QLineEdit::textChanged, this, &MainWindow::on_owner_textChanged);
    connect(ui->owner, &QLineEdit::textChanged, this, &MainWindow::on_owner_textChanged);
    connect(ui->volume, &QLineEdit::textChanged, this, &MainWindow::on_owner_textChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    PrintJob *job = info.getActualData();
    if (job != nullptr) {
        fillForm(job);
    }
    ui->btnUndo->setEnabled(info.hasStates());
    job = nullptr;
}

void MainWindow::btnCalcPressed()
{
    QString co=ui->copies->text();
    QString vo=ui->volume->text();
    bool ok1=false;
    bool ok2=false;
    double d_co=co.toDouble(&ok1);
    double d_vo=vo.toDouble(&ok2);
    if (!ok1 || !ok2){
        QMessageBox::warning(this, "Ошибка", "Введите числа в поле веса и колличества копий!");
        ui->cost->clear();
        return;
    }
    PrintJob *job = processForm();
    showCost(job);
    info.add(job);
    ui->btnUndo->setEnabled(true);
    job = nullptr;
}

void MainWindow::btnUndoPressed()
{
    info.undo();
}


PrintJob *MainWindow::processForm()
{
    return new PrintJob(
        ui->owner->text(),
        ui->volume->text().toInt(),
        ui->copies->text().toInt(),
        ui->quality->currentIndex(),
        ui->materialType->currentIndex()
        );
}


void MainWindow::fillForm(PrintJob *job)
{
    ui->owner->setText(job->getOwner());
    ui->volume->setText(QString::number(job->getVolume()));
    ui->copies->setText(QString::number(job->getCopies()));
    ui->materialType->setCurrentIndex(static_cast<int>(job->getType()));
    ui->quality->setCurrentIndex(job->getQualityIndex());
}

void MainWindow::showCost(PrintJob *job)
{
    int cost = CalculationFacade::getCost(job);
    ui->cost->setText(QString::number(cost) + " руб.");
}


void MainWindow::on_owner_textChanged(const QString &arg1)
{
    ui->cost->setText("");
}

