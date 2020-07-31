/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_M6Path;
    QPushButton *pushButton_M6File;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_Filename;
    QLabel *label_5;
    QLineEdit *lineEdit_Producer;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_Lambda;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_Rho;
    QLabel *label_6;
    QTableWidget *tableWidget;
    QPushButton *pushButton_AddRow;
    QPushButton *pushButton_DeleteRow;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Create;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(730, 568);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_M6Path = new QLineEdit(centralWidget);
        lineEdit_M6Path->setObjectName(QString::fromUtf8("lineEdit_M6Path"));

        gridLayout_2->addWidget(lineEdit_M6Path, 0, 1, 1, 1);

        pushButton_M6File = new QPushButton(centralWidget);
        pushButton_M6File->setObjectName(QString::fromUtf8("pushButton_M6File"));

        gridLayout_2->addWidget(pushButton_M6File, 0, 2, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_Filename = new QLineEdit(groupBox);
        lineEdit_Filename->setObjectName(QString::fromUtf8("lineEdit_Filename"));

        gridLayout->addWidget(lineEdit_Filename, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        lineEdit_Producer = new QLineEdit(groupBox);
        lineEdit_Producer->setObjectName(QString::fromUtf8("lineEdit_Producer"));

        gridLayout->addWidget(lineEdit_Producer, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        doubleSpinBox_Lambda = new QDoubleSpinBox(groupBox);
        doubleSpinBox_Lambda->setObjectName(QString::fromUtf8("doubleSpinBox_Lambda"));
        doubleSpinBox_Lambda->setMinimum(0.050000000000000);
        doubleSpinBox_Lambda->setMaximum(1000.000000000000000);
        doubleSpinBox_Lambda->setSingleStep(0.100000000000000);

        gridLayout->addWidget(doubleSpinBox_Lambda, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        doubleSpinBox_Rho = new QDoubleSpinBox(groupBox);
        doubleSpinBox_Rho->setObjectName(QString::fromUtf8("doubleSpinBox_Rho"));
        doubleSpinBox_Rho->setMinimum(1.000000000000000);
        doubleSpinBox_Rho->setMaximum(10000.000000000000000);
        doubleSpinBox_Rho->setValue(1500.000000000000000);

        gridLayout->addWidget(doubleSpinBox_Rho, 3, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setWordWrap(true);

        gridLayout->addWidget(label_6, 4, 0, 1, 2);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setMinimumSectionSize(28);
        tableWidget->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);

        gridLayout->addWidget(tableWidget, 5, 0, 3, 2);

        pushButton_AddRow = new QPushButton(groupBox);
        pushButton_AddRow->setObjectName(QString::fromUtf8("pushButton_AddRow"));

        gridLayout->addWidget(pushButton_AddRow, 5, 2, 1, 1);

        pushButton_DeleteRow = new QPushButton(groupBox);
        pushButton_DeleteRow->setObjectName(QString::fromUtf8("pushButton_DeleteRow"));

        gridLayout->addWidget(pushButton_DeleteRow, 6, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 7, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 2, 2);

        verticalSpacer = new QSpacerItem(20, 435, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 2, 1, 1);

        pushButton_Create = new QPushButton(centralWidget);
        pushButton_Create->setObjectName(QString::fromUtf8("pushButton_Create"));

        gridLayout_2->addWidget(pushButton_Create, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 730, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Speicherpfad", nullptr));
        pushButton_M6File->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Parameter", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Materialname", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Producer", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Conductivity [W/mK]", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Density [kg/m\302\263]", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "In die folgende Tabelle zugeh\303\266rige Temperatur und Enthalpie in aufsteigender Reihenfolge eintragen.", nullptr));
        pushButton_AddRow->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_DeleteRow->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_Create->setText(QCoreApplication::translate("MainWindow", "Create File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
