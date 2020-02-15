#ifndef OBSBASICCOURSELIST_H
#define OBSBASICCOURSELIST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OBSBasicCourseList; }
QT_END_NAMESPACE

class OBSBasicCourseList : public QMainWindow
{
    Q_OBJECT

public:
    OBSBasicCourseList(QWidget *parent = nullptr);
    ~OBSBasicCourseList();

private:
    Ui::OBSBasicCourseList *ui;
};
#endif // OBSBASICCOURSELIST_H
