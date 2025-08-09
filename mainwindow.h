#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QtNetwork/QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void buttonLoadPath();
    void buttonNextStep();
    void httpReadyRead();
    void httpDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void httpDownloadFinshed();

private:
    Ui::MainWindow *ui;
    QPixmap originalPixmap;
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    QFile *saveFile;
    QString savePath;
    QUrl url;
};
#endif // MAINWINDOW_H
