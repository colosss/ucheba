#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "agencyfacade.h"
#include "agencyobserver.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QString>
#include <QVector>

class QComboBox;
class QTableView;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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
    void completeDealPressed();
    void cancelDealPressed();
    void showClientDealsPressed();
    void showPropertyDealsPressed();
    void findMatchesPressed();
    void resetFilterPressed();
    void seedPressed();
    void clearPressed();
    void showSummaryPressed();
    void tabChanged(int index);
    void updateDealAmount();

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
    QString moneyText(int value) const;
    int selectedTableId(QTableView *view, const QStandardItemModel &model) const;
    int comboCurrentId(QComboBox *box) const;
};

#endif
