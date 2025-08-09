/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *loadPathButton;
    QLineEdit *installPathEdit;
    QLabel *bgImageLabel;
    QPushButton *nextStepButton;
    QProgressBar *progressBar;
    QLabel *progressLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(865, 613);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loadPathButton = new QPushButton(centralwidget);
        loadPathButton->setObjectName("loadPathButton");
        loadPathButton->setGeometry(QRect(540, 510, 111, 31));
        installPathEdit = new QLineEdit(centralwidget);
        installPathEdit->setObjectName("installPathEdit");
        installPathEdit->setGeometry(QRect(40, 510, 451, 31));
        bgImageLabel = new QLabel(centralwidget);
        bgImageLabel->setObjectName("bgImageLabel");
        bgImageLabel->setGeometry(QRect(-10, -10, 921, 701));
        nextStepButton = new QPushButton(centralwidget);
        nextStepButton->setObjectName("nextStepButton");
        nextStepButton->setGeometry(QRect(700, 510, 111, 31));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(40, 520, 591, 16));
        progressBar->setMinimumSize(QSize(0, 16));
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setValue(24);
        progressLabel = new QLabel(centralwidget);
        progressLabel->setObjectName("progressLabel");
        progressLabel->setGeometry(QRect(40, 540, 191, 16));
        MainWindow->setCentralWidget(centralwidget);
        bgImageLabel->raise();
        installPathEdit->raise();
        loadPathButton->raise();
        nextStepButton->raise();
        progressBar->raise();
        progressLabel->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loadPathButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        bgImageLabel->setText(QString());
        nextStepButton->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\346\255\245", nullptr));
        progressLabel->setText(QCoreApplication::translate("MainWindow", "\345\267\262\344\270\213\350\275\275: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
