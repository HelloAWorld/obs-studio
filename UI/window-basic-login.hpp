#ifndef OBSBASICLOGIN_H
#define OBSBASICLOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OBSBasicLogin;
}
QT_END_NAMESPACE

class OBSBasicLogin : public QMainWindow {
	Q_OBJECT

public:
	OBSBasicLogin(QWidget *parent = nullptr);
	~OBSBasicLogin();

	void OBSInit(){};
private slots:
	void on_m_btnlogin_clicked();
	void on_m_btnsignin_clicked();

private:
	int Login(const std::string &strUserName,
		  const std::string &strPassword, std::string &strOutErrorMsg);

private:
	Ui::OBSBasicLogin *ui;
	std::string strToken;
	std::string account;
	int userId;
	int usertype;
};
#endif // OBSBASICLOGIN_H
