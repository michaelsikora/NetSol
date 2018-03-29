#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include <stdlib.h>
#include <vector>
#include <QResource>
#include <QXmlStreamReader>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_status(new QLabel),
    m_console(new Console),
    m_settings(new SettingsDialog),
    m_serial(new QSerialPort(this)),
    m_volume(0)
{
    ui->setupUi(this);
    m_console->setEnabled(false);
    ui->verticalLayout->addWidget(m_console);
    //ui->volumeLabel->setText(QString::number(0));

    QToolBar *toolbar = new QToolBar();
    ui->verticalLayout->addWidget(toolbar);

    // Add Action Buttons to toolbar
    toolbar->addAction(ui->actionConnect);
    toolbar->addAction(ui->actionDisconnect);
    toolbar->addAction(ui->actionConfigure);
    toolbar->addAction(ui->actionClear);
    toolbar->addAction(ui->actionQuit);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->actionClear->setEnabled(true);
    ui->actionQuit->setEnabled(true);

    // Setup Icons for buttons
    QIcon *connectIcon = new QIcon(QString("images/connect.png"));
    QIcon *disconnectIcon = new QIcon(QString("images/disconnect.png"));
    QIcon *configIcon = new QIcon(QString("images/settings.png"));
    QIcon *clearIcon = new QIcon(QString("images/clear.png"));
    QIcon *quitIcon = new QIcon(QString("images/application-exit.png"));
    QIcon *NETSOLicon = new QIcon(QString("images/NETSOL.png"));
    ui->actionConnect->setIcon(*connectIcon);
    ui->actionDisconnect->setIcon(*disconnectIcon);
    ui->actionConfigure->setIcon(*configIcon);
    ui->actionClear->setIcon(*clearIcon);
    ui->actionQuit->setIcon(*quitIcon);

    this->setWindowIcon(*(NETSOLicon));

    ui->statusBar->addWidget(m_status);
    this->setWindowTitle(QString("Netsol : Solar Car Telemetry Desktop Application"));
    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(m_console, &Console::getData, this, &MainWindow::writeData);

    loadCANconfig();
    loadTabLabels();

}

MainWindow::~MainWindow()
{
    delete m_settings;
    delete ui;
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
    qDebug() << p.name;
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
        qDebug() << QString("Cannot open") << p.name;
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
    QMessageBox::about(this, tr("About Netsol : Solar Car Telemtry Desktop Application"),
                       tr("The <b>Solar Car Telemtry Desktop Application</b> is designed for"
                          "connecting to a serial device using the Qt Serial Port module."
                          " The Serial Port implementation was modified from the standard Qt"
                          "Example called terminal that is included with the Qt5 release."));
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
    connect(ui->actionClear, &QAction::triggered, m_console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    ui->menuWindow->addAction(ui->actionConfigure);
    ui->menuFile->addAction(ui->actionClear);
    ui->menuFile->addAction(ui->actionQuit);
    ui->menuAbout->addAction(ui->actionAbout);
    ui->menuAbout->addAction(ui->actionAboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::loadCANconfig() { // Loads in the CAN message structure from the CANconfig.xml file
    const QString fileName = QStringLiteral("CANconfig.xml");
    QFile instanceFile(fileName);
    if (!instanceFile.open(QIODevice::ReadOnly)) { // open in readonly
        qWarning() << "Cannot open";
        return;
    }
    // Use Qt Native XML reader
    QXmlStreamReader *xmlReader = new QXmlStreamReader(&instanceFile);
    xmlReader->readNextStartElement(); // Skips the enclosing CAN tags

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
            // Read next element
            QXmlStreamReader::TokenType token = xmlReader->readNext();

            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }

            // read next element
            if(token == QXmlStreamReader::StartElement) {
                QString value = xmlReader->name().toString();
                if(value == "section") { // SECTION tags
                    QString title = xmlReader->attributes().value("title").toString();
                    qDebug() << "Section title : " << title;
                    titles->append(title);
                }
                CANsection tempSection;

                while(xmlReader->readNextStartElement()) {
                    value = xmlReader->name().toString();
                    qDebug() << value;
                    CANmessage tempMessage;
                    if (value == "message") { // MESSAGE TAGS
                        tempMessage.address = xmlReader->attributes().value("address").toString();

                        while(xmlReader->readNextStartElement()) {
                            value = xmlReader->name().toString();
                            if (value == "data") { // DATA TAGS
                                tempMessage.labels.append(xmlReader->attributes().value("label").toString());
                                tempMessage.types.append(xmlReader->attributes().value("type").toString());
                            }
                            xmlReader->readNext();
                        }
                        xmlReader->readNext();
                    }
                    tempSection.messages.append(tempMessage);

                }
                dataList->append(tempSection);
            }
    }

    qDebug() << titles->length(); // number of sections read in. Should be 7 with given data spec.

    if(xmlReader->hasError()) {
            QMessageBox::critical(this,
            "xmlFile.xml Parse Error",xmlReader->errorString(),
            QMessageBox::Ok);
            return;
    }

    //close reader and flush file
    xmlReader->clear();
    instanceFile.close();
}

void MainWindow::loadTabLabels(){
    ui->tabWidget->clear();
    for(int index = 0; index < titles->length(); index++) {
        QWidget *tab = new QWidget;
        ui->tabWidget->addTab(tab,titles->at(index));
        QVBoxLayout *tablay = new QVBoxLayout;

        QGroupBox *formGroupBox = new QGroupBox(titles->at(index));
        QFormLayout *layout = new QFormLayout;

        CANsection tempCANsection;
        tempCANsection = dataList->at(index);
        for(int i = 0; i < tempCANsection.messages.length(); i++){
            for(int j = 0; j < tempCANsection.messages.at(i).labels.length(); j++) {
//                QHBoxLayout hbox;
//                hbox.addWidget(new QLabel(tempCANsection.messages.at(i).address));
                QString temp = tempCANsection.messages.at(i).labels.at(j);
//                hbox.addWidget(new QLabel(tempCANsection.messages.at(i).types.at(j)));

                layout->addRow(new QLabel(temp), new QLabel(tr("No message")));
            }
        }

        formGroupBox->setLayout(layout);
        tablay->addWidget(formGroupBox);
        tab->setLayout(tablay);
    }
}
