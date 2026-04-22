/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_1;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *line_2;
    QLineEdit *line_1;
    QRadioButton *add;
    QRadioButton *minus;
    QRadioButton *multiply;
    QRadioButton *divine;
    QPushButton *allow;
    QLabel *otv;
    QMenuBar *menubar;
    QMenu *menu_4431;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(949, 594);
        QFont font;
        font.setPointSize(25);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName("label_1");
        label_1->setFont(font);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        formLayout->setLayout(2, QFormLayout::ItemRole::LabelRole, verticalLayout);

        horizontalSpacer = new QSpacerItem(308, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        formLayout->setItem(2, QFormLayout::ItemRole::FieldRole, horizontalSpacer);

        line_2 = new QLineEdit(centralwidget);
        line_2->setObjectName("line_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, line_2);

        line_1 = new QLineEdit(centralwidget);
        line_1->setObjectName("line_1");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, line_1);


        verticalLayout_2->addLayout(formLayout);

        add = new QRadioButton(centralwidget);
        add->setObjectName("add");

        verticalLayout_2->addWidget(add);

        minus = new QRadioButton(centralwidget);
        minus->setObjectName("minus");

        verticalLayout_2->addWidget(minus);

        multiply = new QRadioButton(centralwidget);
        multiply->setObjectName("multiply");

        verticalLayout_2->addWidget(multiply);

        divine = new QRadioButton(centralwidget);
        divine->setObjectName("divine");

        verticalLayout_2->addWidget(divine);

        allow = new QPushButton(centralwidget);
        allow->setObjectName("allow");

        verticalLayout_2->addWidget(allow);

        otv = new QLabel(centralwidget);
        otv->setObjectName("otv");

        verticalLayout_2->addWidget(otv);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 949, 50));
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
        label_1->setText(QCoreApplication::translate("MainWindow", "1-\320\265 \321\207\320\270\321\201\320\273\320\276: ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "2-\320\265 \321\207\320\270\321\201\320\273\320\276: ", nullptr));
        add->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\270\321\202\321\214", nullptr));
        minus->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\207\320\265\321\201\321\202\321\214", nullptr));
        multiply->setText(QCoreApplication::translate("MainWindow", "\320\243\320\274\320\275\320\276\320\266\320\270\321\202\321\214", nullptr));
        divine->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273\320\270\321\202\321\214", nullptr));
        allow->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        otv->setText(QString());
        menu_4431->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\207\320\275\320\265\320\262 \320\241\320\265\321\200\320\263\320\265\320\271 \320\236\320\273\320\265\320\263\320\276\320\262\320\270\321\207 4431", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
