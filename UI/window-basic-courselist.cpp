#include "window-basic-courselist.h"
#include "./ui_OBSBasicCourseList.h"
#include <qstandarditemmodel.h>
#include <qmessagebox.h>

OBSBasicCourseList::OBSBasicCourseList(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::OBSBasicCourseList)
{
	ui->setupUi(this);
}

OBSBasicCourseList::~OBSBasicCourseList()
{
	delete ui;
}

void OBSBasicCourseList::OBSInit()
{
	InitCourseList();
}

void OBSBasicCourseList::on_listView_doubleClicked(const QModelIndex &index)
{
	QMessageBox::critical(NULL, "tips", "doubleclicked", QMessageBox::Ok, QMessageBox::Ok);
	QStandardItemModel *model = (QStandardItemModel *)ui->listView->model();
	QStandardItem *item = model->itemFromIndex(index);
	if (item) {
		std::string text = item->data().toString().toStdString();
		return;
	}
	
}

void OBSBasicCourseList::onClicked(QModelIndex index) {
	QMessageBox::critical(NULL, "tips", "clicked", QMessageBox::Ok,
			      QMessageBox::Ok);
	return;
}

void OBSBasicCourseList::InitCourseList()
{
	QStandardItem *s1;
	QStandardItem *s2;
	QStandardItem *s3;
	QStandardItem *s4;
	QStandardItem *s5;
	QStandardItem *s6;
	QStandardItemModel *slm;
	QListView *listview = ui->listView;
	listview->setViewMode(QListView::IconMode);
	listview->setMovement(QListView::Free);
	listview->setIconSize(QSize(100, 100));
	listview->setGridSize(QSize(150, 100));
	//listview->setGeometry(0,0,480,272);
	listview->setResizeMode(QListView::Fixed);
	listview->setLayoutMode(QListView::SinglePass);
	//s1=new QStandardItem(QIcon(":/515.png"),"普通员工");
	//s2=new QStandardItem(QIcon(":/t01e28c73faf31c0d8c.jpg"),"领导");

	const char *path =
		"D:\\code\\work\\obs-studio\\obs-studio\\UI\\build-2-Desktop_Qt_5_14_1_MSVC2017_32bit-Debug\\1.png";
	s1 = new QStandardItem(QIcon(path), "emploee");
	s2 = new QStandardItem(QIcon(path), "emploer");
	s3 = new QStandardItem(QIcon(path), "huangling");
	s4 = new QStandardItem(QIcon(path), "bailing");
	s5 = new QStandardItem(QIcon(path), "jinling");
	s6 = new QStandardItem(QIcon(path), "heiling");
	slm = new QStandardItemModel(this);
	slm->appendRow(s1);
	slm->appendRow(s2);
	slm->appendRow(s3);
	slm->appendRow(s4);
	slm->appendRow(s5);
	slm->appendRow(s6);

	listview->setModel(slm);

	connect(listview, SIGNAL(clicked(QModelIndex)), this,
		SLOT(onClicked(QModelIndex)));
}

