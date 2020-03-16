#ifndef OBSBASICCOURSELIST_H
#define OBSBASICCOURSELIST_H

#include <QMainWindow>
#include <qstandarditemmodel.h>
#include <qscrollbar.h>
#include "json11.hpp"

#pragma execution_character_set("utf-8")

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
	void SetUseInfo(const std::string &account, const std::string &strToken,
			int userId, int userType);
	int InitLoadCourseList();

private slots:
	void on_listView_doubleClicked(const QModelIndex &index);
	void onClicked(QModelIndex);
	void onSliderChanged(int p);

private:
	void InitCourseList();
	Ui::OBSBasicCourseList *ui;
	QScrollBar *m_vscrollBar;
	QStandardItemModel *m_slm;
	QStandardItem *m_selectedItem;
	std::string m_account;
	std::string m_strToken;
	int m_usertype;
	int m_userId;
	int m_current;
	std::map<QStandardItem *, json11::Json> m_mapResult;
};
#endif // OBSBASICCOURSELIST_H
