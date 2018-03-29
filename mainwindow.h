#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QLabel>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

struct CANmessage
{
    CANmessage() {}
    QString address;
    QStringList types;
    QStringList labels;
};

struct CANsection {
    int numMessages;
    QList<CANmessage> messages;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_Exit_triggered();

    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();
    void showStatusMessage(const QString &message);
    void loadCANconfig();
    void loadTabLabels();

private:
    Ui::MainWindow *ui = nullptr;
    QLabel *m_status = nullptr;
    Console *m_console = nullptr;
    SettingsDialog *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
    uint32_t m_volume;

    QStringList *titles = new QStringList;
    QList<CANsection> *dataList = new QList<CANsection>;

};

#endif // MAINWINDOW_H
