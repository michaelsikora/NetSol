/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Exit;
    QAction *actionConnection_Settings;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionAbout;
    QAction *actionQuit;
    QWidget *centralWidget;
    QLabel *label;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QLabel *volumeLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *m_status;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 400);
        MainWindow->setMinimumSize(QSize(400, 400));
        MainWindow->setMaximumSize(QSize(400, 400));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        actionConnection_Settings = new QAction(MainWindow);
        actionConnection_Settings->setObjectName(QStringLiteral("actionConnection_Settings"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 341, 16));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(90, 40, 160, 22));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 47, 13));
        volumeLabel = new QLabel(centralWidget);
        volumeLabel->setObjectName(QStringLiteral("volumeLabel"));
        volumeLabel->setGeometry(QRect(290, 40, 47, 13));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 100, 371, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_status = new QLabel(centralWidget);
        m_status->setObjectName(QStringLiteral("m_status"));
        m_status->setGeometry(QRect(10, 70, 47, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuAbout->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", nullptr));
        actionConnection_Settings->setText(QApplication::translate("MainWindow", "Connection Settings", nullptr));
        actionConnect->setText(QApplication::translate("MainWindow", "&Connect", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "connect", nullptr));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "disconnect", nullptr));
#endif // QT_NO_TOOLTIP
        actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "configure", nullptr));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        label->setText(QApplication::translate("MainWindow", "This is a test application for reading serial data in a Qt App", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Slide 1", nullptr));
        volumeLabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        m_status->setText(QApplication::translate("MainWindow", "Port: ", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        menuWindow->setTitle(QApplication::translate("MainWindow", "&Window", nullptr));
        menuAbout->setTitle(QApplication::translate("MainWindow", "&About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
