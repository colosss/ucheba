#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QAbstractItemView>
#include <QAction>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QTableView>
#include <QTextBrowser>
#include <algorithm>

static QStandardItem *item(const QString &text)
{
    QStandardItem *value = new QStandardItem(text);
    value->setEditable(false);
    return value;
}

Property PropertyFactory::create(int id, const QString &type, const QString &address, int rooms, double area, int price)
{
    return Property{id, type, address, rooms, area, price, "Свободен"};
}

void AgencyFacade::addObserver(AgencyObserver *observer)
{
    if (!observers.contains(observer)) {
        observers.append(observer);
    }
}

void AgencyFacade::removeObserver(AgencyObserver *observer)
{
    observers.removeAll(observer);
}

const QVector<Property> &AgencyFacade::properties() const
{
    return propertyList;
}

const QVector<Client> &AgencyFacade::clients() const
{
    return clientList;
}

const QVector<Deal> &AgencyFacade::deals() const
{
    return dealList;
}

bool AgencyFacade::addProperty(const Property &property, QString &error)
{
    if (property.id <= 0) {
        error = "Код объекта должен быть положительным";
        return false;
    }
    if (property.address.trimmed().isEmpty()) {
        error = "Введите адрес объекта";
        return false;
    }
    if (propertyIndexById(property.id) != -1) {
        error = "Объект с таким кодом уже есть";
        return false;
    }
    propertyList.append(property);
    notifyObservers();
    return true;
}

bool AgencyFacade::addClient(const Client &client, QString &error)
{
    if (client.id <= 0) {
        error = "Код клиента должен быть положительным";
        return false;
    }
    if (client.fullName.trimmed().isEmpty()) {
        error = "Введите ФИО клиента";
        return false;
    }
    if (client.phone.trimmed().isEmpty()) {
        error = "Введите телефон клиента";
        return false;
    }
    if (clientIndexById(client.id) != -1) {
        error = "Клиент с таким кодом уже есть";
        return false;
    }
    clientList.append(client);
    notifyObservers();
    return true;
}

bool AgencyFacade::addDeal(const Deal &deal, QString &error)
{
    int clientIndex = clientIndexById(deal.clientId);
    int propertyIndex = propertyIndexById(deal.propertyId);
    if (deal.id <= 0) {
        error = "Код сделки должен быть положительным";
        return false;
    }
    if (dealIndexById(deal.id) != -1) {
        error = "Сделка с таким кодом уже есть";
        return false;
    }
    if (clientIndex == -1) {
        error = "Выберите существующего клиента";
        return false;
    }
    if (propertyIndex == -1) {
        error = "Выберите существующий объект недвижимости";
        return false;
    }
    const Property &property = propertyList[propertyIndex];
    if (property.status == "Продан" || property.status == "Сдан") {
        error = "По выбранному объекту уже завершена сделка";
        return false;
    }
    if (deal.amount <= 0) {
        error = "Сумма сделки должна быть положительной";
        return false;
    }
    dealList.append(deal);
    refreshPropertyStatus(deal.propertyId);
    notifyObservers();
    return true;
}

bool AgencyFacade::removeProperty(int id, QString &error)
{
    int index = propertyIndexById(id);
    if (index == -1) {
        error = "Выберите объект для удаления";
        return false;
    }
    for (const Deal &deal : dealList) {
        if (deal.propertyId == id) {
            error = "Нельзя удалить объект, который участвует в сделках";
            return false;
        }
    }
    propertyList.removeAt(index);
    notifyObservers();
    return true;
}

bool AgencyFacade::removeClient(int id, QString &error)
{
    int index = clientIndexById(id);
    if (index == -1) {
        error = "Выберите клиента для удаления";
        return false;
    }
    for (const Deal &deal : dealList) {
        if (deal.clientId == id) {
            error = "Нельзя удалить клиента, который участвует в сделках";
            return false;
        }
    }
    clientList.removeAt(index);
    notifyObservers();
    return true;
}

bool AgencyFacade::removeDeal(int id, QString &error)
{
    int index = dealIndexById(id);
    if (index == -1) {
        error = "Выберите сделку для удаления";
        return false;
    }
    int propertyId = dealList[index].propertyId;
    dealList.removeAt(index);
    refreshPropertyStatus(propertyId);
    notifyObservers();
    return true;
}

void AgencyFacade::clear()
{
    propertyList.clear();
    clientList.clear();
    dealList.clear();
    notifyObservers();
}

void AgencyFacade::seed()
{
    propertyList.clear();
    clientList.clear();
    dealList.clear();

    propertyList.append(PropertyFactory::create(101, "Квартира", "Невский проспект, 12", 2, 58.4, 7400000));
    propertyList.append(PropertyFactory::create(102, "Дом", "Солнечная улица, 8", 5, 146.0, 12800000));
    propertyList.append(PropertyFactory::create(103, "Коммерческое помещение", "Лиговский проспект, 50", 1, 82.5, 9600000));
    propertyList.append(PropertyFactory::create(104, "Квартира", "Московский проспект, 144", 3, 76.2, 8900000));
    propertyList.append(PropertyFactory::create(105, "Участок", "пос. Зеленый бор, участок 17", 0, 900.0, 3100000));

    clientList.append(Client{201, "Иванов Илья Сергеевич", "+7-921-100-01-01", "Квартира", 9000000});
    clientList.append(Client{202, "Петрова Анна Олеговна", "+7-911-105-23-35", "Дом", 15000000});
    clientList.append(Client{203, "Сидоров Максим Павлович", "+7-911-107-07-07", "Коммерческое помещение", 10000000});
    clientList.append(Client{204, "Кузнецова Мария Игоревна", "+7-981-222-32-11", "Участок", 3500000});

    dealList.append(Deal{301, 201, 101, "Бронь", QDate::currentDate().addDays(-3).toString("dd.MM.yyyy"), 7400000, "Оформлена"});
    dealList.append(Deal{302, 203, 103, "Аренда", QDate::currentDate().addDays(-1).toString("dd.MM.yyyy"), 85000, "Выполнена"});

    refreshPropertyStatus(101);
    refreshPropertyStatus(103);
    notifyObservers();
}

QVector<Property> AgencyFacade::availablePropertiesForClient(int clientId) const
{
    QVector<Property> result;
    int index = clientIndexById(clientId);
    if (index == -1) {
        return result;
    }
    const Client &client = clientList[index];
    for (const Property &property : propertyList) {
        bool statusOk = property.status == "Свободен" || property.status == "Забронирован";
        bool typeOk = property.type == client.needType;
        bool budgetOk = property.price <= client.maxBudget;
        if (statusOk && typeOk && budgetOk) {
            result.append(property);
        }
    }
    return result;
}

QVector<Deal> AgencyFacade::dealsByClient(int clientId) const
{
    QVector<Deal> result;
    for (const Deal &deal : dealList) {
        if (deal.clientId == clientId) {
            result.append(deal);
        }
    }
    return result;
}

QVector<Deal> AgencyFacade::dealsByProperty(int propertyId) const
{
    QVector<Deal> result;
    for (const Deal &deal : dealList) {
        if (deal.propertyId == propertyId) {
            result.append(deal);
        }
    }
    return result;
}

int AgencyFacade::totalRevenue() const
{
    int sum = 0;
    for (const Deal &deal : dealList) {
        if (deal.status != "Отменена") {
            sum += deal.amount;
        }
    }
    return sum;
}

int AgencyFacade::propertyIndexById(int id) const
{
    for (int i = 0; i < propertyList.size(); ++i) {
        if (propertyList[i].id == id) {
            return i;
        }
    }
    return -1;
}

int AgencyFacade::clientIndexById(int id) const
{
    for (int i = 0; i < clientList.size(); ++i) {
        if (clientList[i].id == id) {
            return i;
        }
    }
    return -1;
}

int AgencyFacade::dealIndexById(int id) const
{
    for (int i = 0; i < dealList.size(); ++i) {
        if (dealList[i].id == id) {
            return i;
        }
    }
    return -1;
}

void AgencyFacade::notifyObservers()
{
    for (AgencyObserver *observer : observers) {
        if (observer != nullptr) {
            observer->agencyChanged();
        }
    }
}

void AgencyFacade::refreshPropertyStatus(int propertyId)
{
    int propertyIndex = propertyIndexById(propertyId);
    if (propertyIndex == -1) {
        return;
    }
    QString status = "Свободен";
    for (const Deal &deal : dealList) {
        if (deal.propertyId != propertyId || deal.status == "Отменена") {
            continue;
        }
        if (deal.operation == "Продажа" && deal.status == "Выполнена") {
            status = "Продан";
        } else if (deal.operation == "Аренда" && deal.status == "Выполнена") {
            status = "Сдан";
        } else if (deal.operation == "Бронь") {
            status = "Забронирован";
        }
    }
    propertyList[propertyIndex].status = status;
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
    Client client{
        ui->clientIdSpin->value(),
        ui->clientNameEdit->text(),
        ui->clientPhoneEdit->text(),
        ui->clientNeedTypeCombo->currentText(),
        ui->clientBudgetSpin->value()
    };
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
    Deal deal{
        ui->dealIdSpin->value(),
        comboCurrentId(ui->dealClientCombo),
        comboCurrentId(ui->dealPropertyCombo),
        ui->dealOperationCombo->currentText(),
        ui->dealDateEdit->date().toString("dd.MM.yyyy"),
        ui->dealAmountSpin->value(),
        ui->dealStatusCombo->currentText()
    };
    QString error;
    if (!agency.addDeal(deal, error)) {
        QMessageBox::warning(this, "Ошибка", error);
        return;
    }
    clearDealForm();
    showMessage("Сделка добавлена");
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
    text += QString("Сумма активных сделок: %1 руб.\n\n").arg(agency.totalRevenue());
    text += "Связь многие-ко-многим реализована через таблицу сделок: один клиент может иметь несколько сделок, и один объект может участвовать в истории нескольких сделок.";
    ui->summaryBrowser->setText(text);
    ui->tabWidget->setCurrentWidget(ui->tabSearch);
}

void MainWindow::tabChanged(int index)
{
    if (ui->tabWidget->widget(index) == ui->tabSearch) {
        showSummaryPressed();
    }
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
    ui->dealStatusCombo->addItems({"Оформлена", "Выполнена", "Отменена"});

    ui->propertyIdSpin->setMaximum(999999);
    ui->propertyRoomsSpin->setMaximum(30);
    ui->propertyAreaSpin->setMaximum(10000.0);
    ui->propertyAreaSpin->setDecimals(1);
    ui->propertyPriceSpin->setMaximum(1000000000);
    ui->clientIdSpin->setMaximum(999999);
    ui->clientBudgetSpin->setMaximum(1000000000);
    ui->dealIdSpin->setMaximum(999999);
    ui->dealAmountSpin->setMaximum(1000000000);
    ui->dealDateEdit->setDate(QDate::currentDate());
    ui->dealDateEdit->setCalendarPopup(true);
}

void MainWindow::connectInterface()
{
    connect(ui->btnAddProperty, &QPushButton::clicked, this, &MainWindow::addPropertyPressed);
    connect(ui->btnRemoveProperty, &QPushButton::clicked, this, &MainWindow::removePropertyPressed);
    connect(ui->btnAddClient, &QPushButton::clicked, this, &MainWindow::addClientPressed);
    connect(ui->btnRemoveClient, &QPushButton::clicked, this, &MainWindow::removeClientPressed);
    connect(ui->btnAddDeal, &QPushButton::clicked, this, &MainWindow::addDealPressed);
    connect(ui->btnRemoveDeal, &QPushButton::clicked, this, &MainWindow::removeDealPressed);
    connect(ui->btnShowClientDeals, &QPushButton::clicked, this, &MainWindow::showClientDealsPressed);
    connect(ui->btnShowPropertyDeals, &QPushButton::clicked, this, &MainWindow::showPropertyDealsPressed);
    connect(ui->btnFindMatches, &QPushButton::clicked, this, &MainWindow::findMatchesPressed);
    connect(ui->btnResetFilter, &QPushButton::clicked, this, &MainWindow::resetFilterPressed);
    connect(ui->actionSeed, &QAction::triggered, this, &MainWindow::seedPressed);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::clearPressed);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionSummary, &QAction::triggered, this, &MainWindow::showSummaryPressed);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);
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
        row << item(QString::number(property.id));
        row << item(property.type);
        row << item(property.address);
        row << item(QString::number(property.rooms));
        row << item(QString::number(property.area, 'f', 1));
        row << item(QString::number(property.price));
        row << item(property.status);
        propertyModel.appendRow(row);
    }
}

void MainWindow::refreshClientTable(const QVector<Client> &items)
{
    clientModel.removeRows(0, clientModel.rowCount());
    for (const Client &client : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(client.id));
        row << item(client.fullName);
        row << item(client.phone);
        row << item(client.needType);
        row << item(QString::number(client.maxBudget));
        clientModel.appendRow(row);
    }
}

void MainWindow::refreshDealTable(const QVector<Deal> &items)
{
    dealModel.removeRows(0, dealModel.rowCount());
    for (const Deal &deal : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(deal.id));
        row << item(QString::number(deal.clientId));
        row << item(QString::number(deal.propertyId));
        row << item(deal.operation);
        row << item(deal.date);
        row << item(QString::number(deal.amount));
        row << item(deal.status);
        dealModel.appendRow(row);
    }
}

void MainWindow::refreshResultTable(const QVector<Property> &items)
{
    resultModel.removeRows(0, resultModel.rowCount());
    for (const Property &property : items) {
        QList<QStandardItem *> row;
        row << item(QString::number(property.id));
        row << item(property.type);
        row << item(property.address);
        row << item(QString::number(property.rooms));
        row << item(QString::number(property.area, 'f', 1));
        row << item(QString::number(property.price));
        row << item(property.status);
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
        QString text = QString("%1 - %2").arg(client.id).arg(client.fullName);
        ui->dealClientCombo->addItem(text, client.id);
        ui->filterClientCombo->addItem(text, client.id);
    }

    ui->dealPropertyCombo->clear();
    ui->filterPropertyCombo->clear();
    for (const Property &property : agency.properties()) {
        QString text = QString("%1 - %2, %3").arg(property.id).arg(property.type).arg(property.address);
        if (property.status != "Продан" && property.status != "Сдан") {
            ui->dealPropertyCombo->addItem(text, property.id);
        }
        ui->filterPropertyCombo->addItem(text, property.id);
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
    ui->dealAmountSpin->setValue(0);
    ui->dealDateEdit->setDate(QDate::currentDate());
}

void MainWindow::showMessage(const QString &message)
{
    statusBar()->showMessage(message, 4000);
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
