/********************************************************************************
** Form generated from reading UI file 'OBSBasicWebView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBSBASICWEBVIEW_H
#define UI_OBSBASICWEBVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBSBasicWebView
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OBSBasicWebView)
    {
        if (OBSBasicWebView->objectName().isEmpty())
            OBSBasicWebView->setObjectName(QString::fromUtf8("OBSBasicWebView"));
        OBSBasicWebView->resize(800, 600);
        centralwidget = new QWidget(OBSBasicWebView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        OBSBasicWebView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OBSBasicWebView);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        OBSBasicWebView->setMenuBar(menubar);
        statusbar = new QStatusBar(OBSBasicWebView);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OBSBasicWebView->setStatusBar(statusbar);

        retranslateUi(OBSBasicWebView);

        QMetaObject::connectSlotsByName(OBSBasicWebView);
    } // setupUi

    void retranslateUi(QMainWindow *OBSBasicWebView)
    {
        OBSBasicWebView->setWindowTitle(QCoreApplication::translate("OBSBasicWebView", "OBSBasicWebView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBSBasicWebView: public Ui_OBSBasicWebView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBSBASICWEBVIEW_H
