#ifndef OBSBASICLOGIN_H
#define OBSBASICLOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OBSBasicLogin; }
QT_END_NAMESPACE

class OBSBasicLogin : public QMainWindow
{
    Q_OBJECT

public:
    OBSBasicLogin(QWidget *parent = nullptr);
    ~OBSBasicLogin();

    void OBSInit(){};
    private slots:
    void on_m_btnlogin_clicked();

private:
    Ui::OBSBasicLogin *ui;
};
#endif // OBSBASICLOGIN_H
