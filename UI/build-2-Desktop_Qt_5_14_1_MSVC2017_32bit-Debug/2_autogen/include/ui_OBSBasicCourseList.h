/********************************************************************************
** Form generated from reading UI file 'OBSBasicCourseList.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBSBASICCOURSELIST_H
#define UI_OBSBASICCOURSELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OBSBasicCourseList
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OBSBasicCourseList)
    {
        if (OBSBasicCourseList->objectName().isEmpty())
            OBSBasicCourseList->setObjectName(QString::fromUtf8("OBSBasicCourseList"));
        OBSBasicCourseList->resize(200, 730);
        centralwidget = new QWidget(OBSBasicCourseList);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 10, 181, 730));
        OBSBasicCourseList->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OBSBasicCourseList);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 200, 22));
        OBSBasicCourseList->setMenuBar(menubar);
        statusbar = new QStatusBar(OBSBasicCourseList);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OBSBasicCourseList->setStatusBar(statusbar);

        retranslateUi(OBSBasicCourseList);

        QMetaObject::connectSlotsByName(OBSBasicCourseList);
    } // setupUi

    void retranslateUi(QMainWindow *OBSBasicCourseList)
    {
        OBSBasicCourseList->setWindowTitle(QCoreApplication::translate("OBSBasicCourseList", "OBSBasicCourseList", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OBSBasicCourseList: public Ui_OBSBasicCourseList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBSBASICCOURSELIST_H
