#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>
#include <QString>

class QComboBox;
class QTableView;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Property
{
    int id;
    QString type;
    QString address;
    int rooms;
    double area;
    int price;
    QString status;
};

struct Client
{
    int id;
    QString fullName;
    QString phone;
    QString needType;
    int maxBudget;
};

struct Deal
{
    int id;
    int clientId;
    int propertyId;
    QString operation;
    QString date;
    int amount;
    QString status;
};

class PropertyFactory
{
public:
    static Property create(int id, const QString &type, const QString &address, int rooms, double area, int price);
};

class AgencyObserver
{
public:
    virtual ~AgencyObserver() = default;
    virtual void agencyChanged() = 0;
};

class AgencyFacade
{
public:
    void addObserver(AgencyObserver *observer);
    void removeObserver(AgencyObserver *observer);

    const QVector<Property> &properties() const;
    const QVector<Client> &clients() const;
    const QVector<Deal> &deals() const;

    bool addProperty(const Property &property, QString &error);
    bool addClient(const Client &client, QString &error);
    bool addDeal(const Deal &deal, QString &error);
    bool removeProperty(int id, QString &error);
    bool removeClient(int id, QString &error);
    bool removeDeal(int id, QString &error);
    void clear();
    void seed();

    QVector<Property> availablePropertiesForClient(int clientId) const;
    QVector<Deal> dealsByClient(int clientId) const;
    QVector<Deal> dealsByProperty(int propertyId) const;
    int totalRevenue() const;

private:
    QVector<Property> propertyList;
    QVector<Client> clientList;
    QVector<Deal> dealList;
    QVector<AgencyObserver *> observers;

    int propertyIndexById(int id) const;
    int clientIndexById(int id) const;
    int dealIndexById(int id) const;
    void notifyObservers();
    void refreshPropertyStatus(int propertyId);
};

class MainWindow : public QMainWindow, public AgencyObserver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void agencyChanged() override;

private slots:
    void addPropertyPressed();
    void removePropertyPressed();
    void addClientPressed();
    void removeClientPressed();
    void addDealPressed();
    void removeDealPressed();
    void showClientDealsPressed();
    void showPropertyDealsPressed();
    void findMatchesPressed();
    void resetFilterPressed();
    void seedPressed();
    void clearPressed();
    void showSummaryPressed();
    void tabChanged(int index);

private:
    Ui::MainWindow *ui;
    AgencyFacade agency;
    QStandardItemModel propertyModel;
    QStandardItemModel clientModel;
    QStandardItemModel dealModel;
    QStandardItemModel resultModel;

    void configureTables();
    void configureInputs();
    void connectInterface();
    void refreshAll();
    void refreshPropertyTable(const QVector<Property> &items);
    void refreshClientTable(const QVector<Client> &items);
    void refreshDealTable(const QVector<Deal> &items);
    void refreshResultTable(const QVector<Property> &items);
    void fillComboBoxes();
    void clearPropertyForm();
    void clearClientForm();
    void clearDealForm();
    void showMessage(const QString &message);
    int selectedTableId(QTableView *view, const QStandardItemModel &model) const;
    int comboCurrentId(QComboBox *box) const;
};
#endif
