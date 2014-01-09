/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Sep 29 18:13:16 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *broserpushBtn;
    QPushButton *closepushBtn;
    QTextBrowser *fileContextBrowser;
    QLabel *notelab;
    QTextEdit *edittextEdit;
    QPushButton *uppushBtn;
    QPushButton *downpushBtn;
    QPushButton *aboutpushBtn;
    QPushButton *calcpushBtn;
    QTextBrowser *pathlab;
    QPushButton *broserdirpushBtn;
    QLabel *resultLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(791, 643);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        broserpushBtn = new QPushButton(centralWidget);
        broserpushBtn->setObjectName(QString::fromUtf8("broserpushBtn"));
        broserpushBtn->setGeometry(QRect(40, 0, 291, 51));
        QFont font;
        font.setPointSize(36);
        broserpushBtn->setFont(font);
        closepushBtn = new QPushButton(centralWidget);
        closepushBtn->setObjectName(QString::fromUtf8("closepushBtn"));
        closepushBtn->setGeometry(QRect(710, 490, 71, 81));
        QFont font1;
        font1.setPointSize(24);
        closepushBtn->setFont(font1);
        fileContextBrowser = new QTextBrowser(centralWidget);
        fileContextBrowser->setObjectName(QString::fromUtf8("fileContextBrowser"));
        fileContextBrowser->setGeometry(QRect(40, 70, 671, 211));
        notelab = new QLabel(centralWidget);
        notelab->setObjectName(QString::fromUtf8("notelab"));
        notelab->setGeometry(QRect(40, 290, 101, 31));
        QFont font2;
        font2.setPointSize(18);
        notelab->setFont(font2);
        notelab->setMouseTracking(false);
        notelab->setFocusPolicy(Qt::NoFocus);
        notelab->setAcceptDrops(false);
        notelab->setAutoFillBackground(false);
        notelab->setScaledContents(true);
        edittextEdit = new QTextEdit(centralWidget);
        edittextEdit->setObjectName(QString::fromUtf8("edittextEdit"));
        edittextEdit->setGeometry(QRect(40, 320, 671, 271));
        QFont font3;
        font3.setPointSize(9);
        edittextEdit->setFont(font3);
        uppushBtn = new QPushButton(centralWidget);
        uppushBtn->setObjectName(QString::fromUtf8("uppushBtn"));
        uppushBtn->setGeometry(QRect(720, 70, 51, 101));
        QFont font4;
        font4.setPointSize(72);
        uppushBtn->setFont(font4);
        downpushBtn = new QPushButton(centralWidget);
        downpushBtn->setObjectName(QString::fromUtf8("downpushBtn"));
        downpushBtn->setGeometry(QRect(720, 180, 51, 101));
        downpushBtn->setFont(font4);
        aboutpushBtn = new QPushButton(centralWidget);
        aboutpushBtn->setObjectName(QString::fromUtf8("aboutpushBtn"));
        aboutpushBtn->setGeometry(QRect(710, 430, 71, 51));
        calcpushBtn = new QPushButton(centralWidget);
        calcpushBtn->setObjectName(QString::fromUtf8("calcpushBtn"));
        calcpushBtn->setGeometry(QRect(730, 320, 51, 41));
        pathlab = new QTextBrowser(centralWidget);
        pathlab->setObjectName(QString::fromUtf8("pathlab"));
        pathlab->setGeometry(QRect(40, 47, 671, 20));
        broserdirpushBtn = new QPushButton(centralWidget);
        broserdirpushBtn->setObjectName(QString::fromUtf8("broserdirpushBtn"));
        broserdirpushBtn->setGeometry(QRect(370, 0, 331, 51));
        broserdirpushBtn->setFont(font);
        resultLabel = new QLabel(centralWidget);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(720, 370, 61, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 791, 19));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\250\213\345\272\217\346\263\250\351\207\212\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        broserpushBtn->setToolTip(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266\345\244\271\346\210\226\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        broserpushBtn->setText(QApplication::translate("MainWindow", "Broser File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        closepushBtn->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:24pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\205\263\351\227\255</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        closepushBtn->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        notelab->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\263\250\351\207\212", 0, QApplication::UnicodeUTF8));
        uppushBtn->setText(QApplication::translate("MainWindow", "\342\206\221", 0, QApplication::UnicodeUTF8));
        downpushBtn->setText(QApplication::translate("MainWindow", "\342\206\223", 0, QApplication::UnicodeUTF8));
        aboutpushBtn->setText(QApplication::translate("MainWindow", "about", 0, QApplication::UnicodeUTF8));
        calcpushBtn->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\231\250", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        broserdirpushBtn->setToolTip(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266\345\244\271\346\210\226\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        broserdirpushBtn->setText(QApplication::translate("MainWindow", "Broser Dir", 0, QApplication::UnicodeUTF8));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
