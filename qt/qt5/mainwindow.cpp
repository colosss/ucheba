#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_textChanged);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_2_textChanged);
    connect(ui->pushButton_con_1, &QPushButton::released, this, &MainWindow::show_element_by_id);
    connect(ui->pushButton_con_2, &QPushButton::released, this, &MainWindow::delete_element_by_id);
    connect(ui->pushButton_con_3, &QPushButton::released, this, &MainWindow::delete_element_by_mean);
    connect(ui->pushButton_prog_1, &QPushButton::released, this, &MainWindow::add_element);
    connect(ui->pushButton_prog_2, &QPushButton::released, this, &MainWindow::sum_elements);
    connect(ui->pushButton_prog_3, &QPushButton::released, this, &MainWindow::sum_2_elemnts);
    connect(ui->pushButton_hard_1, &QPushButton::released, this, &MainWindow::on_pushButton_hard_1_released);
    connect(ui->pushButton_hard_2, &QPushButton::released, this, &MainWindow::on_pushButton_hard_2_released);
    connect(ui->pushButton_hard_3, &QPushButton::released, this, &MainWindow::clear_m);
    connect(ui->pushButton_my_1, &QPushButton::released, this, &MainWindow::nu_null_list);
    connect(ui->pushButton_my_2, &QPushButton::released, this, &MainWindow::min_max);

    ui->pushButton_con_1->setDisabled(true);
    ui->pushButton_con_2->setDisabled(true);
    ui->pushButton_con_3->setDisabled(true);
    ui->pushButton_hard_2->setDisabled(true);
    ui->pushButton_hard_3->setDisabled(true);
    ui->pushButton_my_1->setDisabled(true);
    ui->pushButton_my_2->setDisabled(true);
    ui->pushButton_prog_1->setDisabled(true);
    ui->pushButton_prog_2->setDisabled(true);
    ui->pushButton_prog_3->setDisabled(true);
    ui->lineEdit->setDisabled(true);
    ui->lineEdit_3->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_modify_widget() {
    ui->listWidget_modify->clear();
    for (const int &v : list_modify)
        ui->listWidget_modify->addItem(QString::number(v));
}

void MainWindow::on_lineEdit_textChanged(const QString &)
{
    bool has_text = !ui->lineEdit->text().isEmpty();
    bool has_list = !list_modify.isEmpty();
    ui->pushButton_con_1->setDisabled(!(has_text && has_list));
    ui->pushButton_con_2->setDisabled(!(has_text && has_list));
}

void MainWindow::on_lineEdit_2_textChanged(const QString &)
{
    bool has_text = !ui->lineEdit_2->text().isEmpty();
    bool has_list = !list_modify.isEmpty();
    ui->pushButton_prog_1->setDisabled(!has_text);
    ui->pushButton_con_3->setDisabled(!(has_text && has_list));
}

void MainWindow::on_pushButton_hard_1_released()
{
    list_ishod.clear();
    list_modify.clear();
    ui->listWidget_ishod->clear();
    ui->listWidget_modify->clear();

    QString temp_file_name = ui->comboBox_file_name->currentText();
    QFile file("/home/mifugi/ucheba/qt/qt5/" + temp_file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + temp_file_name);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        bool ok;
        int val = line.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Файл содержит не целое число: \"" + line + "\"");
            list_ishod.clear();
            list_modify.clear();
            ui->listWidget_ishod->clear();
            file.close();
            return;
        }
        list_ishod.append(val);
    }
    file.close();

    if (list_ishod.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл пуст!");
        return;
    }

    for (const int &v : list_ishod)
        ui->listWidget_ishod->addItem(QString::number(v));

    list_modify = list_ishod;
    refresh_modify_widget();

    ui->lineEdit->setDisabled(false);
    ui->pushButton_my_1->setDisabled(false);
    ui->pushButton_my_2->setDisabled(false);
    ui->pushButton_hard_2->setDisabled(false);
    ui->pushButton_hard_3->setDisabled(false);
    ui->pushButton_prog_2->setDisabled(false);
    ui->pushButton_prog_3->setDisabled(false);

    if (!ui->lineEdit_2->text().isEmpty())
        ui->pushButton_con_3->setDisabled(false);

    if (!ui->lineEdit->text().isEmpty()){
        ui->pushButton_con_1->setDisabled(false);
        ui->pushButton_con_2->setDisabled(false);
    }
}

void MainWindow::on_pushButton_hard_2_released()
{
    if (list_modify.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Преобразованная коллекция пуста — нечего сохранять!");
        return;
    }

    QString temp_file_name = ui->comboBox_file_name->currentText();
    QFile file("/home/mifugi/ucheba/qt/qt5/modify_" + temp_file_name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи: modify_" + temp_file_name);
        return;
    }

    QTextStream out(&file);
    for (const int &v : list_modify)
        out << v << "\n";
    file.close();
}

void MainWindow::show_element_by_id() {
    bool ok;
    int idx = ui->lineEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Индекс должен быть целым числом!");
        return;
    }
    if (idx < 0 || idx >= list_modify.size()) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Индекс %1 вне диапазона [0, %2]!").arg(idx).arg(list_modify.size() - 1));
        return;
    }
    ui->lineEdit_3->setText(QString::number(list_modify.value(idx)));
}

void MainWindow::delete_element_by_id() {
    bool ok;
    int idx = ui->lineEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Индекс должен быть целым числом!");
        return;
    }
    if (idx < 0 || idx >= list_modify.size()) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Индекс %1 вне диапазона [0, %2]!").arg(idx).arg(list_modify.size() - 1));
        return;
    }
    list_modify.removeAt(idx);
    refresh_modify_widget();
}

void MainWindow::delete_element_by_mean() {
    bool ok;
    int val = ui->lineEdit_2->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Значение должно быть целым числом!");
        return;
    }
    int idx = list_modify.indexOf(val);
    if (idx == -1) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Элемент со значением %1 не найден в преобразованной коллекции!").arg(val));
        return;
    }
    list_modify.removeAt(idx);
    refresh_modify_widget();
}

void MainWindow::add_element() {
    bool ok;
    int val = ui->lineEdit_2->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Значение должно быть целым числом!");
        return;
    }
    list_modify.append(val);
    ui->listWidget_modify->addItem(QString::number(val));

    ui->pushButton_prog_2->setDisabled(false);
    ui->pushButton_prog_3->setDisabled(false);
    ui->pushButton_hard_2->setDisabled(false);
    ui->pushButton_hard_3->setDisabled(false);
    ui->pushButton_my_1->setDisabled(false);
    ui->pushButton_my_2->setDisabled(false);
    ui->lineEdit->setDisabled(false);
}

void MainWindow::sum_elements() {
    if (list_modify.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Преобразованная коллекция пуста!");
        return;
    }
    long long sum = 0;
    for (const int &v : list_modify) sum += v;
    ui->lineEdit_3->setText(QString::number(sum));
}

void MainWindow::sum_2_elemnts() {
    if (list_modify.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Преобразованная коллекция пуста!");
        return;
    }
    long long sum = 0;
    for (const int &v : list_modify)
        if (v % 2 == 0) sum += v;
    ui->lineEdit_3->setText(QString::number(sum));
}

void MainWindow::clear_m() {
    list_ishod.clear();
    list_modify.clear();
    ui->listWidget_ishod->clear();
    ui->listWidget_modify->clear();
    ui->lineEdit_3->clear();

    ui->pushButton_con_1->setDisabled(true);
    ui->pushButton_con_2->setDisabled(true);
    ui->pushButton_con_3->setDisabled(true);
    ui->pushButton_hard_2->setDisabled(true);
    ui->pushButton_hard_3->setDisabled(true);
    ui->pushButton_my_1->setDisabled(true);
    ui->pushButton_my_2->setDisabled(true);
    ui->pushButton_prog_2->setDisabled(true);
    ui->pushButton_prog_3->setDisabled(true);
    ui->lineEdit->setDisabled(true);
}

void MainWindow::nu_null_list() {
    if (list_modify.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Преобразованная коллекция пуста!");
        return;
    }
    QList<int> result;
    for (const int &v : list_modify)
        if (v != 0) result.append(v);

    if (result.isEmpty()) {
        QMessageBox::warning(this, "Результат", "Все элементы равны нулю — результирующий список пуст!");
        return;
    }
    list_modify = result;
    refresh_modify_widget();
}

void MainWindow::min_max() {
    if (list_modify.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Преобразованная коллекция пуста!");
        return;
    }
    if (list_modify.size() == 1) {
        QMessageBox::warning(this, "Ошибка", "В коллекции только один элемент — операция не имеет смысла!");
        return;
    }

    int mn = *std::min_element(list_modify.begin(), list_modify.end());
    int mx = *std::max_element(list_modify.begin(), list_modify.end());

    if (mn == mx) {
        QMessageBox::warning(this, "Ошибка", "Все элементы равны — min == max, диапазон пуст!");
        return;
    }

    int idx_min = list_modify.indexOf(mn);
    int idx_max = list_modify.indexOf(mx);
    if (idx_min > idx_max) std::swap(idx_min, idx_max);

    list_modify = list_modify.mid(idx_min, idx_max - idx_min + 1);
    refresh_modify_widget();

    long long product = 1;
    for (const int &v : list_modify) product *= v;
    ui->lineEdit_3->setText(QString::number(product));
}

void MainWindow::on_pushButton_con_1_released() {}
void MainWindow::on_pushButton_con_2_released() {}
void MainWindow::on_textBrowser_ishod_textChanged() {}
void MainWindow::on_listWidget_ishod_itemSelectionChanged() {}
