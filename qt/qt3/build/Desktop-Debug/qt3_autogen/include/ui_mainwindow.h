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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_ves;
    QLineEdit *lineEdit_ves;
    QLabel *label_time;
    QLineEdit *lineEdit_time;
    QLabel *label_type_3;
    QLabel *label_type;
    QLabel *label;
    QPushButton *pushButton_raschet;
    QLabel *label_itog;
    QGroupBox *groupBox;
    QRadioButton *rb_obich;
    QRadioButton *rb_sroch;
    QGroupBox *groupBox_2;
    QRadioButton *rb_pla;
    QRadioButton *rb_pla_plus;
    QRadioButton *rb_petg;
    QRadioButton *rb_petg_rapid_plus;
    QRadioButton *rb_tpu;
    QLabel *label_itog_otv;
    QMenuBar *menubar;
    QMenu *menu_4431;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(706, 493);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_ves = new QLabel(centralwidget);
        label_ves->setObjectName("label_ves");
        label_ves->setGeometry(QRect(120, 50, 53, 26));
        QFont font;
        font.setPointSize(12);
        label_ves->setFont(font);
        lineEdit_ves = new QLineEdit(centralwidget);
        lineEdit_ves->setObjectName("lineEdit_ves");
        lineEdit_ves->setGeometry(QRect(180, 50, 481, 26));
        label_time = new QLabel(centralwidget);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(10, 90, 159, 26));
        label_time->setFont(font);
        lineEdit_time = new QLineEdit(centralwidget);
        lineEdit_time->setObjectName("lineEdit_time");
        lineEdit_time->setGeometry(QRect(180, 90, 481, 26));
        label_type_3 = new QLabel(centralwidget);
        label_type_3->setObjectName("label_type_3");
        label_type_3->setGeometry(QRect(80, 130, 87, 38));
        label_type_3->setFont(font);
        label_type = new QLabel(centralwidget);
        label_type->setObjectName("label_type");
        label_type->setGeometry(QRect(60, 230, 107, 38));
        label_type->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(440, 120, 221, 121));
        pushButton_raschet = new QPushButton(centralwidget);
        pushButton_raschet->setObjectName("pushButton_raschet");
        pushButton_raschet->setEnabled(true);
        pushButton_raschet->setGeometry(QRect(200, 360, 477, 26));
        pushButton_raschet->setCheckable(false);
        pushButton_raschet->setAutoDefault(false);
        label_itog = new QLabel(centralwidget);
        label_itog->setObjectName("label_itog");
        label_itog->setGeometry(QRect(40, 400, 146, 22));
        label_itog->setFont(font);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(180, 140, 161, 81));
        rb_obich = new QRadioButton(groupBox);
        rb_obich->setObjectName("rb_obich");
        rb_obich->setGeometry(QRect(0, 10, 226, 23));
        rb_obich->setChecked(true);
        rb_sroch = new QRadioButton(groupBox);
        rb_sroch->setObjectName("rb_sroch");
        rb_sroch->setGeometry(QRect(0, 40, 226, 23));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(180, 230, 201, 111));
        rb_pla = new QRadioButton(groupBox_2);
        rb_pla->setObjectName("rb_pla");
        rb_pla->setGeometry(QRect(0, 10, 226, 23));
        rb_pla->setChecked(true);
        rb_pla_plus = new QRadioButton(groupBox_2);
        rb_pla_plus->setObjectName("rb_pla_plus");
        rb_pla_plus->setGeometry(QRect(0, 30, 226, 23));
        rb_petg = new QRadioButton(groupBox_2);
        rb_petg->setObjectName("rb_petg");
        rb_petg->setGeometry(QRect(0, 50, 226, 23));
        rb_petg_rapid_plus = new QRadioButton(groupBox_2);
        rb_petg_rapid_plus->setObjectName("rb_petg_rapid_plus");
        rb_petg_rapid_plus->setGeometry(QRect(0, 70, 226, 23));
        rb_tpu = new QRadioButton(groupBox_2);
        rb_tpu->setObjectName("rb_tpu");
        rb_tpu->setGeometry(QRect(0, 90, 226, 23));
        label_itog_otv = new QLabel(centralwidget);
        label_itog_otv->setObjectName("label_itog_otv");
        label_itog_otv->setGeometry(QRect(190, 400, 481, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 706, 23));
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
        label_type_3->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\267\320\260\320\272\320\260\320\267\320\260:", nullptr));
        label_type->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\260:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270 \320\277\320\273\320\260\321\201\321\202\320\270\320\272\320\260:\n"
"PLA/PETG + 0\321\200\n"
"PLA PLUS/PETG RAPID PLUS + 50\321\200\n"
"TPU + 150\321\200\n"
"\320\236\320\261\321\213\321\207\320\275\321\213\320\271 \320\267\320\260\320\272\320\260\320\267 +0\321\200\n"
"\320\241\321\200\320\276\321\207\320\275\321\213\320\271 \320\267\320\260\320\272\320\260\320\267 + 1000\321\200", nullptr));
        pushButton_raschet->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202", nullptr));
        label_itog->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\277\320\265\321\207\320\260\321\202\320\270:", nullptr));
        groupBox->setTitle(QString());
        rb_obich->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\213\321\207\320\275\321\213\320\271", nullptr));
        rb_sroch->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\276\321\207\320\275\321\213\320\271 \320\267\320\260\320\272\320\260\320\267", nullptr));
        groupBox_2->setTitle(QString());
        rb_pla->setText(QCoreApplication::translate("MainWindow", "PLA", nullptr));
        rb_pla_plus->setText(QCoreApplication::translate("MainWindow", "PLA PLUS", nullptr));
        rb_petg->setText(QCoreApplication::translate("MainWindow", "PETG", nullptr));
        rb_petg_rapid_plus->setText(QCoreApplication::translate("MainWindow", "PETG RAPID PLUS", nullptr));
        rb_tpu->setText(QCoreApplication::translate("MainWindow", "TPU", nullptr));
        label_itog_otv->setText(QString());
        menu_4431->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\207\320\275\320\265\320\262 \320\241\320\265\321\200\320\263\320\265\320\271 4431", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
