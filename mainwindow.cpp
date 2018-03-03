#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_console(new Console),
    m_settings(new SettingsDialog),
    m_serial(new QSerialPort(this)),
    m_volume(0)
{
    ui->setupUi(this);
    m_console->setEnabled(false);
    ui->verticalLayout->addWidget(m_console);
    ui->volumeLabel->setText(QString::number(0));

    QToolBar *toolbar = new QToolBar();
    ui->verticalLayout->addWidget(toolbar);

    // Add Action Buttons to toolbar
    toolbar->addAction(ui->actionConnect);
    toolbar->addAction(ui->actionDisconnect);
    toolbar->addAction(ui->actionConfigure);
    toolbar->addAction(ui->actionQuit);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->actionQuit->setEnabled(true);

    // Setup Icons for buttons
    QIcon *connectIcon = new QIcon(QString("images/connect.png"));
    QIcon *disconnectIcon = new QIcon(QString("images/disconnect.png"));
    QIcon *configIcon = new QIcon(QString("images/settings.png"));
    QIcon *quitIcon = new QIcon(QString("images/application-exit.png"));
    ui->actionConnect->setIcon(*connectIcon);
    ui->actionDisconnect->setIcon(*disconnectIcon);
    ui->actionConfigure->setIcon(*configIcon);
    ui->actionQuit->setIcon(*quitIcon);

    ui->statusBar->addWidget(m_status);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_console, &Console::getData, this, &MainWindow::writeData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->volumeLabel->setText(QVariant(position).toString());
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

//! [4]
void MainWindow::openSerialPort()
{
    qDebug() << "opening Serial Port";
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        m_console->setEnabled(true);
        m_console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();
    m_console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}


void MainWindow::writeData(const QByteArray &data)
{
    m_serial->write(data);
}


void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    m_console->putData(data);
}



void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}


void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
//    connect(ui->actionClear, &QAction::triggered, m_console, &Console::clear);
//    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
//    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    ui->menuWindow->addAction(ui->actionConfigure);
    ui->menuFile->addAction(ui->actionQuit);
    ui->menuAbout->addAction(ui->actionAbout);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}
