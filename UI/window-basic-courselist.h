#ifndef OBSBASICCOURSELIST_H
#define OBSBASICCOURSELIST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OBSBasicCourseList;
}
QT_END_NAMESPACE

class OBSBasicCourseList : public QMainWindow {
	Q_OBJECT

public:
	OBSBasicCourseList(QWidget *parent = nullptr);
	~OBSBasicCourseList();

public:
	void OBSInit();

private slots:
	void on_listView_doubleClicked(const QModelIndex &index);
	void onClicked(QModelIndex);

private:
	void InitCourseList();
	Ui::OBSBasicCourseList *ui;
};
#endif // OBSBASICCOURSELIST_H
