#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "propertyfactory.h"

#include <QAbstractItemView>
#include <QAction>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QHeaderView>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QTableView>
#include <QTabWidget>
#include <QtGlobal>
#include <QTextBrowser>

static QStandardItem *item(const QString &text)
{
    QStandardItem *value = new QStandardItem(text);
    value->setEditable(false);
    return value;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configureTables();
    configureInputs();
    connectInterface();
    agency.addObserver(this);
    agency.seed();
}

MainWindow::~MainWindow()
{
    agency.removeObserver(this);
    delete ui;
}

void MainWindow::agencyChanged()
{
    refreshAll();
}

void MainWindow::addPropertyPressed()
{
    Property property = PropertyFactory::create(
        ui->propertyIdSpin->value(),
        ui->propertyTypeCombo->currentText(),
        ui->propertyAddressEdit->text(),
        ui->propertyRoomsSpin->value(),
        ui->propertyAreaSpin->value(),
        ui->propertyPriceSpin->value()
        );
    QString error;
    if (!agency.addProperty(property, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    clearPropertyForm();
    showMessage("Объект недвижимости добавлен");
}

void MainWindow::removePropertyPressed()
{
    int id = selectedTableId(ui->propertyTableView, propertyModel);
    QString error;
    if (!agency.removeProperty(id, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    showMessage("Объект недвижимости удален");
}

void MainWindow::addClientPressed()
{
    Client client(
        ui->clientIdSpin->value(),
        ui->clientNameEdit->text(),
        ui->clientPhoneEdit->text(),
        ui->clientNeedTypeCombo->currentText(),
        ui->clientBudgetSpin->value()
        );
    QString error;
    if (!agency.addClient(client, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    clearClientForm();
    showMessage("Клиент добавлен");
}

void MainWindow::removeClientPressed()
{
    int id = selectedTableId(ui->clientTableView, clientModel);
    QString error;
    if (!agency.removeClient(id, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    showMessage("Клиент удален");
}

void MainWindow::addDealPressed()
{
    int propertyId = comboCurrentId(ui->dealPropertyCombo);
    Deal deal(
        ui->dealIdSpin->value(),
        comboCurrentId(ui->dealClientCombo),
        propertyId,
        ui->dealOperationCombo->currentText(),
        ui->dealDateEdit->date().toString("dd.MM.yyyy"),
        agency.propertyPrice(propertyId),
        "Оформлена"
        );
    QString error;
    if (!agency.addDeal(deal, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    clearDealForm();
    showMessage("Сделка оформлена");
}

void MainWindow::removeDealPressed()
{
    int id = selectedTableId(ui->dealTableView, dealModel);
    QString error;
    if (!agency.removeDeal(id, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    showMessage("Сделка удалена");
}

void MainWindow::completeDealPressed()
{
    int id = selectedTableId(ui->dealTableView, dealModel);
    QString error;
    if (!agency.completeDeal(id, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    showMessage("Сделка выполнена");
}

void MainWindow::cancelDealPressed()
{
    int id = selectedTableId(ui->dealTableView, dealModel);
    QString error;
    if (!agency.cancelDeal(id, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    showMessage("Сделка отменена");
}

void MainWindow::showClientDealsPressed()
{
    int clientId = comboCurrentId(ui->filterClientCombo);
    QVector<Deal> deals = agency.dealsByClient(clientId);
    refreshDealTable(deals);
    ui->tabWidget->setCurrentWidget(ui->tabDeal);
    showMessage("Показаны сделки выбранного клиента");
}

void MainWindow::showPropertyDealsPressed()
{
    int propertyId = comboCurrentId(ui->filterPropertyCombo);
    QVector<Deal> deals = agency.dealsByProperty(propertyId);
    refreshDealTable(deals);
    ui->tabWidget->setCurrentWidget(ui->tabDeal);
    showMessage("Показаны сделки выбранного объекта");
}

void MainWindow::findMatchesPressed()
{
    int clientId = comboCurrentId(ui->filterClientCombo);
    QVector<Property> properties = agency.availablePropertiesForClient(clientId);
    refreshResultTable(properties);
    ui->summaryBrowser->setText(QString("Найдено подходящих объектов: %1").arg(properties.size()));
    showMessage("Подбор объектов выполнен");
}

void MainWindow::resetFilterPressed()
{
    refreshDealTable(agency.deals());
    refreshResultTable(agency.properties());
    showSummaryPressed();
    showMessage("Фильтр сброшен");
}

void MainWindow::seedPressed()
{
    agency.seed();
    showMessage("Загружен демонстрационный набор данных");
}

void MainWindow::clearPressed()
{
    if (QMessageBox::question(this, "Подтверждение", "Очистить все таблицы?") != QMessageBox::Yes) {
        return;
    }
    agency.clear();
    showMessage("Данные очищены");
}

void MainWindow::showSummaryPressed()
{
    QString text;
    text += "Агентство недвижимости\n";
    text += QString("Объектов: %1\n").arg(agency.properties().size());
    text += QString("Клиентов: %1\n").arg(agency.clients().size());
    text += QString("Сделок: %1\n").arg(agency.deals().size());
    text += QString("Доход по выполненным сделкам: %1\n\n").arg(moneyText(agency.totalRevenue()));
    text += "Связь многие-ко-многим реализована через таблицу сделок. Сделка связывает клиента и объект недвижимости. При выполнении продажи или аренды сумма сделки автоматически берется из стоимости объекта, бюджет клиента уменьшается, а статус объекта меняется на продан или сдан.";
    ui->summaryBrowser->setText(text);
    ui->tabWidget->setCurrentWidget(ui->tabSearch);
}

void MainWindow::tabChanged(int index)
{
    if (ui->tabWidget->widget(index) == ui->tabSearch) {
        showSummaryPressed();
    }
}

void MainWindow::updateDealAmount()
{
    int price = agency.propertyPrice(comboCurrentId(ui->dealPropertyCombo));
    ui->dealAmountEdit->setText(moneyText(price));
}

void MainWindow::configureTables()
{
    propertyModel.setHorizontalHeaderLabels({"Код", "Тип", "Адрес", "Комнат", "Площадь", "Цена", "Статус"});
    clientModel.setHorizontalHeaderLabels({"Код", "ФИО", "Телефон", "Потребность", "Бюджет"});
    dealModel.setHorizontalHeaderLabels({"Код", "Клиент", "Объект", "Операция", "Дата", "Сумма", "Статус"});
    resultModel.setHorizontalHeaderLabels({"Код", "Тип", "Адрес", "Комнат", "Площадь", "Цена", "Статус"});

    ui->propertyTableView->setModel(&propertyModel);
    ui->clientTableView->setModel(&clientModel);
    ui->dealTableView->setModel(&dealModel);
    ui->resultTableView->setModel(&resultModel);

    QVector<QTableView *> tables{ui->propertyTableView, ui->clientTableView, ui->dealTableView, ui->resultTableView};
    for (QTableView *table : tables) {
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->horizontalHeader()->setStretchLastSection(true);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void MainWindow::configureInputs()
{
    ui->propertyTypeCombo->addItems({"Квартира", "Дом", "Коммерческое помещение", "Участок"});
    ui->clientNeedTypeCombo->addItems({"Квартира", "Дом", "Коммерческое помещение", "Участок"});
    ui->dealOperationCombo->addItems({"Бронь", "Продажа", "Аренда"});
    ui->dealStatusCombo->addItem("Оформлена");
    ui->dealStatusCombo->setEnabled(false);
    ui->dealAmountEdit->setReadOnly(true);

    ui->propertyIdSpin->setMaximum(999999);
    ui->propertyRoomsSpin->setMaximum(30);
    ui->propertyAreaSpin->setMaximum(10000.0);
    ui->propertyAreaSpin->setDecimals(1);
    ui->propertyPriceSpin->setMaximum(1000000000);
    ui->clientIdSpin->setMaximum(999999);
    ui->clientBudgetSpin->setMaximum(1000000000);
    ui->dealIdSpin->setMaximum(999999);
    ui->dealDateEdit->setDate(QDate::currentDate());
    ui->dealDateEdit->setCalendarPopup(true);
    updateDealAmount();
}

void MainWindow::connectInterface()
{
    connect(ui->btnAddProperty, &QPushButton::clicked, this, &MainWindow::addPropertyPressed);
    connect(ui->btnRemoveProperty, &QPushButton::clicked, this, &MainWindow::removePropertyPressed);
    connect(ui->btnAddClient, &QPushButton::clicked, this, &MainWindow::addClientPressed);
    connect(ui->btnRemoveClient, &QPushButton::clicked, this, &MainWindow::removeClientPressed);
    connect(ui->btnAddDeal, &QPushButton::clicked, this, &MainWindow::addDealPressed);
    connect(ui->btnRemoveDeal, &QPushButton::clicked, this, &MainWindow::removeDealPressed);
    connect(ui->btnCompleteDeal, &QPushButton::clicked, this, &MainWindow::completeDealPressed);
    connect(ui->btnCancelDeal, &QPushButton::clicked, this, &MainWindow::cancelDealPressed);
    connect(ui->btnShowClientDeals, &QPushButton::clicked, this, &MainWindow::showClientDealsPressed);
    connect(ui->btnShowPropertyDeals, &QPushButton::clicked, this, &MainWindow::showPropertyDealsPressed);
    connect(ui->btnFindMatches, &QPushButton::clicked, this, &MainWindow::findMatchesPressed);
    connect(ui->btnResetFilter, &QPushButton::clicked, this, &MainWindow::resetFilterPressed);
    connect(ui->actionSeed, &QAction::triggered, this, &MainWindow::seedPressed);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clearPressed);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionSummary, &QAction::triggered, this, &MainWindow::showSummaryPressed);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);
    connect(ui->dealPropertyCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateDealAmount);
}

void MainWindow::refreshAll()
{
    refreshPropertyTable(agency.properties());
    refreshClientTable(agency.clients());
    refreshDealTable(agency.deals());
    refreshResultTable(agency.properties());
    fillComboBoxes();
    if (ui->tabWidget->currentWidget() == ui->tabSearch) {
        showSummaryPressed();
    }
}

void MainWindow::refreshPropertyTable(const QVector<Property> &items)
{
    propertyModel.removeRows(0, propertyModel.rowCount());
    for (const Property &property : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(property.id()));
        row << item(property.type());
        row << item(property.address());
        row << item(QString::number(property.rooms()));
        row << item(QString::number(property.area(), 'f', 1));
        row << item(moneyText(property.price()));
        row << item(property.status());
        propertyModel.appendRow(row);
    }
}

void MainWindow::refreshClientTable(const QVector<Client> &items)
{
    clientModel.removeRows(0, clientModel.rowCount());
    for (const Client &client : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(client.id()));
        row << item(client.fullName());
        row << item(client.phone());
        row << item(client.needType());
        row << item(moneyText(client.maxBudget()));
        clientModel.appendRow(row);
    }
}

void MainWindow::refreshDealTable(const QVector<Deal> &items)
{
    dealModel.removeRows(0, dealModel.rowCount());
    for (const Deal &deal : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(deal.id()));
        row << item(QString::number(deal.clientId()));
        row << item(QString::number(deal.propertyId()));
        row << item(deal.operation());
        row << item(deal.date());
        row << item(moneyText(deal.amount()));
        row << item(deal.status());
        dealModel.appendRow(row);
    }
}

void MainWindow::refreshResultTable(const QVector<Property> &items)
{
    resultModel.removeRows(0, resultModel.rowCount());
    for (const Property &property : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(property.id()));
        row << item(property.type());
        row << item(property.address());
        row << item(QString::number(property.rooms()));
        row << item(QString::number(property.area(), 'f', 1));
        row << item(moneyText(property.price()));
        row << item(property.status());
        resultModel.appendRow(row);
    }
}

void MainWindow::fillComboBoxes()
{
    int currentClient = comboCurrentId(ui->dealClientCombo);
    int currentProperty = comboCurrentId(ui->dealPropertyCombo);
    int filterClient = comboCurrentId(ui->filterClientCombo);
    int filterProperty = comboCurrentId(ui->filterPropertyCombo);

    ui->dealClientCombo->clear();
    ui->filterClientCombo->clear();
    for (const Client &client : agency.clients()) {
        QString text = QString("%1 - %2, бюджет %3").arg(client.id()).arg(client.fullName()).arg(moneyText(client.maxBudget()));
        ui->dealClientCombo->addItem(text, client.id());
        ui->filterClientCombo->addItem(text, client.id());
    }

    ui->dealPropertyCombo->clear();
    ui->filterPropertyCombo->clear();
    for (const Property &property : agency.properties()) {
        QString text = QString("%1 - %2, %3, %4").arg(property.id()).arg(property.type()).arg(property.address()).arg(moneyText(property.price()));
        if (property.status() == "Свободен") {
            ui->dealPropertyCombo->addItem(text, property.id());
        }
        ui->filterPropertyCombo->addItem(text, property.id());
    }

    int clientIndex = ui->dealClientCombo->findData(currentClient);
    if (clientIndex >= 0) {
        ui->dealClientCombo->setCurrentIndex(clientIndex);
    }
    int propertyIndex = ui->dealPropertyCombo->findData(currentProperty);
    if (propertyIndex >= 0) {
        ui->dealPropertyCombo->setCurrentIndex(propertyIndex);
    }
    int filterClientIndex = ui->filterClientCombo->findData(filterClient);
    if (filterClientIndex >= 0) {
        ui->filterClientCombo->setCurrentIndex(filterClientIndex);
    }
    int filterPropertyIndex = ui->filterPropertyCombo->findData(filterProperty);
    if (filterPropertyIndex >= 0) {
        ui->filterPropertyCombo->setCurrentIndex(filterPropertyIndex);
    }
    updateDealAmount();
}

void MainWindow::clearPropertyForm()
{
    ui->propertyIdSpin->setValue(ui->propertyIdSpin->value() + 1);
    ui->propertyAddressEdit->clear();
    ui->propertyRoomsSpin->setValue(1);
    ui->propertyAreaSpin->setValue(0.0);
    ui->propertyPriceSpin->setValue(0);
}

void MainWindow::clearClientForm()
{
    ui->clientIdSpin->setValue(ui->clientIdSpin->value() + 1);
    ui->clientNameEdit->clear();
    ui->clientPhoneEdit->clear();
    ui->clientBudgetSpin->setValue(0);
}

void MainWindow::clearDealForm()
{
    ui->dealIdSpin->setValue(ui->dealIdSpin->value() + 1);
    ui->dealDateEdit->setDate(QDate::currentDate());
    updateDealAmount();
}

void MainWindow::showMessage(const QString &message)
{
    statusBar()->showMessage(message, 4000);
}

QString MainWindow::moneyText(int value) const
{
    return QLocale(QLocale::Russian, QLocale::Russia).toString(value) + " руб.";
}

int MainWindow::selectedTableId(QTableView *view, const QStandardItemModel &model) const
{
    QModelIndexList selection = view->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        return -1;
    }
    QModelIndex index = model.index(selection.first().row(), 0);
    return model.data(index).toInt();
}

int MainWindow::comboCurrentId(QComboBox *box) const
{
    if (box->currentIndex() < 0) {
        return -1;
    }
    return box->currentData().toInt();
}
