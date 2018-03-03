#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QVariant>
#include <QString>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_sliderMoved(int position);
    void on_action_Exit_triggered();

    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    Console *m_console = nullptr;
    SettingsDialog *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
    QLabel *m_status = nullptr;
    uint32_t m_volume;

};

#endif // MAINWINDOW_H
