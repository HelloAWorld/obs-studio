#include "window-basic-courselist.h"
#include "./ui_OBSBasicCourseList.h"

OBSBasicCourseList::OBSBasicCourseList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OBSBasicCourseList)
{
    ui->setupUi(this);
}

OBSBasicCourseList::~OBSBasicCourseList()
{
    delete ui;
}

