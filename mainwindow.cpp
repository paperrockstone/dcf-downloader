#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QDebug>
#include <QNetworkReply>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon("/Users/dolph/Downloads/dnf.ico"));

    ui->progressBar->hide();

    ui->progressLabel->hide();

    url = QUrl("https://github.com/aria2/aria2/releases/download/release-1.37.0/aria2-1.37.0-aarch64-linux-android-build1.zip");

    originalPixmap.load("/Users/dolph/Downloads/dnfbackground.png");

    if (originalPixmap.isNull()) {
        qDebug() << "图片加载失败！请检查路径。"; }

    savePath = "/Users/dolph/Downloads";

    ui->installPathEdit->setText(savePath);

    connect(ui->loadPathButton,&QPushButton::clicked,this,&MainWindow::buttonLoadPath);
    connect(ui->nextStepButton,&QPushButton::clicked,this,&MainWindow::buttonNextStep);

    update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonLoadPath()
{
    QString path = QFileDialog::getExistingDirectory(
        this,
        tr("Select Directory"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

    if (!path.isEmpty()) {
        ui->installPathEdit->setText(path);
        savePath = path;
    }

}

void MainWindow::buttonNextStep()
{
    if(ui->nextStepButton->text()=="完成")
    {
        this->close();
    }

    ui->loadPathButton->hide();
    ui->installPathEdit->hide();
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->progressLabel->show();
    ui->nextStepButton->setEnabled(false);
    ui->nextStepButton->setText("完成");

    QDir dir;

    if(!dir.exists(savePath)){
        if(dir.mkdir(savePath)){
            qDebug() << "创建目录成功";
        }
        else{
            qDebug() << "无法创建指定目录";
        }
    }else{
        qDebug() << "目录已存在";
    }

    QString fileName = url.fileName();

    QString fullFilePath = savePath + "/" + fileName;

    if(QFile::exists(fullFilePath)){
        QFile::remove(fullFilePath);
        qDebug() << "覆盖现有文件";
    }

    saveFile = new QFile(fullFilePath);
    if(!saveFile->open(QIODevice::WriteOnly)){
        qDebug() << "无法打开指定目录进行文件写入" << saveFile->errorString();
        delete saveFile;
        saveFile = nullptr;
        return;
    }

    networkManager = new QNetworkAccessManager(this);
    networkReply = networkManager->get(QNetworkRequest(url));

    connect(networkReply, &QNetworkReply::readyRead, this, &MainWindow::httpReadyRead);
    connect(networkReply, &QNetworkReply::downloadProgress, this, &MainWindow::httpDownloadProgress);
    connect(networkReply, &QNetworkReply::finished, this, &MainWindow::httpDownloadFinshed);

}

void MainWindow::httpReadyRead(){
    if(saveFile && saveFile->isOpen()){
        saveFile->write(networkReply->readAll());
    }
}


void MainWindow::httpDownloadProgress(qint64 bytesReceived, qint64 bytesTotal){
    if(bytesTotal > 0){
        ui->progressBar->setMaximum(bytesTotal);
        ui->progressBar->setValue(bytesReceived);
        ui->progressLabel->setText("已下载: " + QString::number((double)bytesReceived/1024/1024,'f',2) + "M /" + \
                                   QString::number((double)bytesTotal/1024/1024,'f',2) + "M"
                                   );
    }
}

void MainWindow::httpDownloadFinshed(){
    if(networkReply->error() != QNetworkReply::NoError){
        qDebug() << "下载失败:" << networkReply->errorString();
        if(saveFile){
            saveFile->remove();
        }
    }else{
        qDebug() << "下载成功";
    }
    if(saveFile){
        saveFile->close();
        delete saveFile;
        saveFile = nullptr;
        ui->nextStepButton->setText("完成");
        ui->nextStepButton->setEnabled(true);
        //QMessageBox msg;
        //msg.setWindowTitle("提示");
        //msg.setText("下载完成，请解压文件");
        //msg.setWindowIcon(QIcon("/Users/dolph/Downloads/dnf.ico"));
        //msg.setIcon(QMessageBox::Information); // Set the information icon
        //msg.exec();
        QMessageBox::information(this,"提示","下载完成，请解压文件");
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    // 调用基类的 paintEvent 确保其他默认绘制行为被执行
    QMainWindow::paintEvent(event);
    if (originalPixmap.isNull()) {
        return; // 如果图片未加载成功，则不绘制
    }
    QPainter painter(this); // 在 MainWindow 上进行绘制

    // 获取 QLabel 的几何信息，用于确定绘制区域
    // 或者，如果你只想在 MainWindow 的特定区域绘制，可以直接使用固定坐标和大小
    QRect labelRect = ui->bgImageLabel->geometry();

    // 缩放原始图片以适应 QLabel 的大小
    QPixmap scaledPixmap = originalPixmap.scaled(labelRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 创建一个新的 QPixmap 用于绘制带有透明度的图片
    QPixmap transparentPixmap(scaledPixmap.size());
    transparentPixmap.fill(Qt::transparent); // 填充为透明背景

    // 在 transparentPixmap 上进行绘制
    QPainter p(&transparentPixmap);
    p.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿以获得更平滑的渐变效果

    // 绘制原始缩放后的图片到透明 QPixmap 上
    p.drawPixmap(0, 0, scaledPixmap);

    QLinearGradient gradient(0, 0, transparentPixmap.width(), 0);
    QLinearGradient gradient2(0, 0, 0, transparentPixmap.height());

    // 从左边缘开始，透明度为0（完全透明）
    gradient.setColorAt(0.0, QColor(0, 0, 0, 0));    // 左边界完全透明
    gradient.setColorAt(0.1, QColor(0, 0, 0, 255));   // 稍微向右，完全不透明
    gradient.setColorAt(0.9, QColor(0, 0, 0, 255));   // 稍微向左，完全不透明
    gradient.setColorAt(1.0, QColor(0, 0, 0, 0));    // 右边界完全透明

    gradient2.setColorAt(0.7, QColor(0, 0, 0, 255));
    gradient2.setColorAt(1.0, QColor(0, 0, 0, 0));
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);

    // 使用渐变填充整个 transparentPixmap 区域
    p.fillRect(transparentPixmap.rect(), gradient);
    p.fillRect(transparentPixmap.rect(), gradient2);
    p.end(); // 结束 transparentPixmap 的绘制

    // 最后，将处理后的 transparentPixmap 绘制到 ui->label 的位置上
    painter.drawPixmap(labelRect.topLeft(), transparentPixmap);
}
