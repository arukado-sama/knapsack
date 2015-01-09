/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QListWidget *displayObjects;
    QLineEdit *linePoidsSac;
    QLineEdit *lineValeur;
    QLineEdit *linePoids;
    QLabel *labelPoids;
    QLabel *labelValeur;
    QPushButton *buttonAdd;
    QLabel *labelPoidsSac;
    QPushButton *buttonDelete;
    QTextBrowser *displayTree;
    QPushButton *buttonDisplay;
    QPushButton *buttonSolve;
    QPushButton *buttonClear;
    QPushButton *buttonAbout;
    QPushButton *buttonExit;
    QPushButton *buttonLoad;
    QPushButton *buttonHow;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(571, 676);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        displayObjects = new QListWidget(centralWidget);
        displayObjects->setObjectName(QStringLiteral("displayObjects"));
        displayObjects->setGeometry(QRect(30, 140, 511, 121));
        displayObjects->setStyleSheet(QStringLiteral(""));
        linePoidsSac = new QLineEdit(centralWidget);
        linePoidsSac->setObjectName(QStringLiteral("linePoidsSac"));
        linePoidsSac->setGeometry(QRect(190, 10, 281, 27));
        lineValeur = new QLineEdit(centralWidget);
        lineValeur->setObjectName(QStringLiteral("lineValeur"));
        lineValeur->setGeometry(QRect(430, 100, 113, 27));
        linePoids = new QLineEdit(centralWidget);
        linePoids->setObjectName(QStringLiteral("linePoids"));
        linePoids->setGeometry(QRect(250, 100, 113, 27));
        labelPoids = new QLabel(centralWidget);
        labelPoids->setObjectName(QStringLiteral("labelPoids"));
        labelPoids->setGeometry(QRect(190, 100, 51, 21));
        labelValeur = new QLabel(centralWidget);
        labelValeur->setObjectName(QStringLiteral("labelValeur"));
        labelValeur->setGeometry(QRect(380, 100, 51, 21));
        buttonAdd = new QPushButton(centralWidget);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setGeometry(QRect(30, 100, 141, 27));
        labelPoidsSac = new QLabel(centralWidget);
        labelPoidsSac->setObjectName(QStringLiteral("labelPoidsSac"));
        labelPoidsSac->setGeometry(QRect(90, 10, 91, 21));
        buttonDelete = new QPushButton(centralWidget);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        buttonDelete->setGeometry(QRect(30, 270, 511, 27));
        displayTree = new QTextBrowser(centralWidget);
        displayTree->setObjectName(QStringLiteral("displayTree"));
        displayTree->setGeometry(QRect(30, 360, 511, 221));
        displayTree->setStyleSheet(QStringLiteral(""));
        buttonDisplay = new QPushButton(centralWidget);
        buttonDisplay->setObjectName(QStringLiteral("buttonDisplay"));
        buttonDisplay->setGeometry(QRect(30, 320, 191, 27));
        buttonSolve = new QPushButton(centralWidget);
        buttonSolve->setObjectName(QStringLiteral("buttonSolve"));
        buttonSolve->setGeometry(QRect(240, 320, 191, 27));
        buttonClear = new QPushButton(centralWidget);
        buttonClear->setObjectName(QStringLiteral("buttonClear"));
        buttonClear->setGeometry(QRect(450, 320, 91, 27));
        buttonClear->setStyleSheet(QStringLiteral(""));
        buttonAbout = new QPushButton(centralWidget);
        buttonAbout->setObjectName(QStringLiteral("buttonAbout"));
        buttonAbout->setGeometry(QRect(210, 590, 151, 27));
        buttonAbout->setStyleSheet(QStringLiteral(""));
        buttonExit = new QPushButton(centralWidget);
        buttonExit->setObjectName(QStringLiteral("buttonExit"));
        buttonExit->setGeometry(QRect(390, 590, 151, 27));
        buttonExit->setStyleSheet(QStringLiteral(""));
        buttonLoad = new QPushButton(centralWidget);
        buttonLoad->setObjectName(QStringLiteral("buttonLoad"));
        buttonLoad->setGeometry(QRect(30, 50, 511, 27));
        buttonHow = new QPushButton(centralWidget);
        buttonHow->setObjectName(QStringLiteral("buttonHow"));
        buttonHow->setGeometry(QRect(30, 590, 151, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 571, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        labelPoids->setText(QApplication::translate("MainWindow", "Weight", 0));
        labelValeur->setText(QApplication::translate("MainWindow", "Value", 0));
        buttonAdd->setText(QApplication::translate("MainWindow", "Add object", 0));
        labelPoidsSac->setText(QApplication::translate("MainWindow", "Sack capacity", 0));
        buttonDelete->setText(QApplication::translate("MainWindow", "Delete selected object", 0));
        buttonDisplay->setText(QApplication::translate("MainWindow", "Display tree (with cutting)", 0));
        buttonSolve->setText(QApplication::translate("MainWindow", "Display best solution", 0));
        buttonClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        buttonAbout->setText(QApplication::translate("MainWindow", "About", 0));
        buttonExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        buttonLoad->setText(QApplication::translate("MainWindow", "Load file", 0));
        buttonHow->setText(QApplication::translate("MainWindow", "How to use", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
