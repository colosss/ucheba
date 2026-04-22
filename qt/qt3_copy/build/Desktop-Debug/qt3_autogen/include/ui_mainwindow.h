/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_ves;
    QLineEdit *lineEdit_ves;
    QLabel *label_time;
    QLineEdit *lineEdit_time;
    QLabel *label_type;
    QComboBox *comboBox_type;
    QPushButton *pushButton_raschet;
    QLabel *label_itog;
    QLabel *label_itog_otv;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menu_4431;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(80, 60, 631, 351));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_ves = new QLabel(formLayoutWidget);
        label_ves->setObjectName("label_ves");
        QFont font;
        font.setPointSize(12);
        label_ves->setFont(font);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_ves);

        lineEdit_ves = new QLineEdit(formLayoutWidget);
        lineEdit_ves->setObjectName("lineEdit_ves");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_ves);

        label_time = new QLabel(formLayoutWidget);
        label_time->setObjectName("label_time");
        label_time->setFont(font);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_time);

        lineEdit_time = new QLineEdit(formLayoutWidget);
        lineEdit_time->setObjectName("lineEdit_time");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_time);

        label_type = new QLabel(formLayoutWidget);
        label_type->setObjectName("label_type");
        label_type->setFont(font);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_type);

        comboBox_type = new QComboBox(formLayoutWidget);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, comboBox_type);

        pushButton_raschet = new QPushButton(formLayoutWidget);
        pushButton_raschet->setObjectName("pushButton_raschet");
        pushButton_raschet->setEnabled(true);
        pushButton_raschet->setCheckable(false);
        pushButton_raschet->setAutoDefault(false);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, pushButton_raschet);

        label_itog = new QLabel(formLayoutWidget);
        label_itog->setObjectName("label_itog");
        label_itog->setFont(font);

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_itog);

        label_itog_otv = new QLabel(formLayoutWidget);
        label_itog_otv->setObjectName("label_itog_otv");
        label_itog_otv->setFont(font);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, label_itog_otv);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, label);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu_4431 = new QMenu(menubar);
        menu_4431->setObjectName("menu_4431");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_4431->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_ves->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\201 (\320\263):", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\277\320\265\321\207\320\260\321\202\320\270 (\320\274\320\270\320\275):", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\260:", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "PLA", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "PLA PLUS", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("MainWindow", "PETG", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("MainWindow", "PETG RAPID PLUS", nullptr));
        comboBox_type->setItemText(4, QCoreApplication::translate("MainWindow", "TPU", nullptr));

        pushButton_raschet->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202", nullptr));
        label_itog->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\277\320\265\321\207\320\260\321\202\320\270:", nullptr));
        label_itog_otv->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\260:\n"
"PLA/PETG + 0\321\200\n"
"PLA PLUS/PETG RAPID PLUS + 50\321\200\n"
"TPU + 150\321\200", nullptr));
        menu_4431->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\207\320\275\320\265\320\262 \320\241\320\265\321\200\320\263\320\265\320\271 4431", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
