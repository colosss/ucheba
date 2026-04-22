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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QCheckBox *chbox_chehol;
    QCheckBox *chbox_zh;
    QCheckBox *chbox_provod;
    QCheckBox *chbox_zarad;
    QCheckBox *chbox_naushniki;
    QCheckBox *chbox_strahovka;
    QVBoxLayout *verticalLayout_6;
    QLabel *main_lable;
    QLabel *image_lable;
    QPushButton *rbutton;
    QLabel *spisok_lable;
    QLabel *spisok_vivod_lable;
    QLabel *itog_lable_2;
    QLabel *otv_coml;
    QHBoxLayout *horizontalLayout_2;
    QLabel *itog_lable;
    QLabel *otv;
    QMenuBar *menubar;
    QMenu *menu_4431;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(914, 1048);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 911, 891));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 100));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        verticalLayout_5->addWidget(label);

        chbox_chehol = new QCheckBox(horizontalLayoutWidget);
        chbox_chehol->setObjectName("chbox_chehol");
        chbox_chehol->setFont(font);
        chbox_chehol->setIconSize(QSize(16, 16));

        verticalLayout_5->addWidget(chbox_chehol);

        chbox_zh = new QCheckBox(horizontalLayoutWidget);
        chbox_zh->setObjectName("chbox_zh");
        chbox_zh->setFont(font);

        verticalLayout_5->addWidget(chbox_zh);

        chbox_provod = new QCheckBox(horizontalLayoutWidget);
        chbox_provod->setObjectName("chbox_provod");
        chbox_provod->setFont(font);

        verticalLayout_5->addWidget(chbox_provod);

        chbox_zarad = new QCheckBox(horizontalLayoutWidget);
        chbox_zarad->setObjectName("chbox_zarad");
        chbox_zarad->setFont(font);

        verticalLayout_5->addWidget(chbox_zarad);

        chbox_naushniki = new QCheckBox(horizontalLayoutWidget);
        chbox_naushniki->setObjectName("chbox_naushniki");
        chbox_naushniki->setFont(font);

        verticalLayout_5->addWidget(chbox_naushniki);

        chbox_strahovka = new QCheckBox(horizontalLayoutWidget);
        chbox_strahovka->setObjectName("chbox_strahovka");
        chbox_strahovka->setFont(font);

        verticalLayout_5->addWidget(chbox_strahovka);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        main_lable = new QLabel(horizontalLayoutWidget);
        main_lable->setObjectName("main_lable");
        main_lable->setFont(font);
        main_lable->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(main_lable);

        image_lable = new QLabel(horizontalLayoutWidget);
        image_lable->setObjectName("image_lable");
        image_lable->setMinimumSize(QSize(200, 250));
        image_lable->setMaximumSize(QSize(200, 250));
        image_lable->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        image_lable->setPixmap(QPixmap(QString::fromUtf8("iphone17.jpg")));
        image_lable->setScaledContents(true);
        image_lable->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(image_lable, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        rbutton = new QPushButton(horizontalLayoutWidget);
        rbutton->setObjectName("rbutton");

        verticalLayout_6->addWidget(rbutton);

        spisok_lable = new QLabel(horizontalLayoutWidget);
        spisok_lable->setObjectName("spisok_lable");
        spisok_lable->setFont(font);

        verticalLayout_6->addWidget(spisok_lable);

        spisok_vivod_lable = new QLabel(horizontalLayoutWidget);
        spisok_vivod_lable->setObjectName("spisok_vivod_lable");
        spisok_vivod_lable->setFont(font);

        verticalLayout_6->addWidget(spisok_vivod_lable);

        itog_lable_2 = new QLabel(horizontalLayoutWidget);
        itog_lable_2->setObjectName("itog_lable_2");
        itog_lable_2->setFont(font);

        verticalLayout_6->addWidget(itog_lable_2);

        otv_coml = new QLabel(horizontalLayoutWidget);
        otv_coml->setObjectName("otv_coml");
        otv_coml->setFont(font);

        verticalLayout_6->addWidget(otv_coml);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        itog_lable = new QLabel(horizontalLayoutWidget);
        itog_lable->setObjectName("itog_lable");
        itog_lable->setFont(font);

        horizontalLayout_2->addWidget(itog_lable);

        otv = new QLabel(horizontalLayoutWidget);
        otv->setObjectName("otv");
        otv->setFont(font);

        horizontalLayout_2->addWidget(otv);


        verticalLayout_6->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_6);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 914, 23));
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
        label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\273\320\265\320\272\321\202\321\203\321\216\321\211\320\270\320\265:", nullptr));
        chbox_chehol->setText(QCoreApplication::translate("MainWindow", "\320\247\320\265\321\205\320\276\320\273 - 3000\321\200", nullptr));
        chbox_zh->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\211\320\270\321\202\320\275\320\276\320\265 \321\201\321\202\320\265\320\272\320\273\320\276 - 500\321\200", nullptr));
        chbox_provod->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\276\320\264 Type-C - 1500\321\200", nullptr));
        chbox_zarad->setText(QCoreApplication::translate("MainWindow", "\320\221\320\273\320\276\320\272 \320\277\320\270\321\202\320\260\320\275\320\270\321\217 - 1500\321\200", nullptr));
        chbox_naushniki->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\203\321\210\320\275\320\270\320\272\320\270 - 3000\321\200", nullptr));
        chbox_strahovka->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\321\205\320\276\320\262\320\272\320\260 - 500\321\200", nullptr));
        main_lable->setText(QCoreApplication::translate("MainWindow", "Iphone 17 Pro Max 256Gb", nullptr));
        image_lable->setText(QString());
        rbutton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\206\320\265\320\275\321\203", nullptr));
        spisok_lable->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \321\202\320\276\320\262\320\260\321\200\320\276\320\262:", nullptr));
        spisok_vivod_lable->setText(QString());
        itog_lable_2->setText(QCoreApplication::translate("MainWindow", "\320\230\321\202\320\276\320\263\320\276\320\262\320\260\321\217 \321\201\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214 \320\272\320\276\320\274\320\277\320\273\320\265\320\272\321\202\321\203\321\216\321\211\320\270\321\205:", nullptr));
        otv_coml->setText(QString());
        itog_lable->setText(QCoreApplication::translate("MainWindow", "\320\230\321\202\320\276\320\263\320\276\320\262\320\260\321\217 \321\206\320\265\320\275\320\260:", nullptr));
        otv->setText(QString());
        menu_4431->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\207\320\275\320\265\320\262 \320\241\320\265\321\200\320\263\320\265\320\271 4431", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
