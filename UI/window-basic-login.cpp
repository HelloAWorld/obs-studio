#include "window-basic-login.hpp"
#include "./ui_obsbasiclogin.h"
#include "window-basic-main.hpp"
#include "CCurlHttpClient.h"
#include <qmessagebox.h>
#include "qt-wrappers.hpp"
#include "time.h"
#include "stdlib.h"
#include "windows.h"

OBSBasicLogin::OBSBasicLogin(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::OBSBasicLogin)
{
	ui->setupUi(this);
}

OBSBasicLogin::~OBSBasicLogin()
{
	delete ui;
}

void OBSBasicLogin::on_m_btnlogin_clicked()
{
	std::string username = ui->m_editusername->displayText().toStdString();
	std::string password = ui->m_editpassword->displayText().toStdString();

	if (username.empty())
	{
		QMessageBox::critical(
			NULL, QTStr("Login.Title"), //QTStr("login failed"),
			QTStr("username is empty"), //QTStr("login failed, check you net , username and password is correct"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	if (password.empty())
	{
		QMessageBox::critical(
			NULL, QTStr("Login.Title"), //QTStr("login failed"),
			QTStr("password is empty"), //QTStr("login failed, check you net , username and password is correct"),
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	int ret = Login(username, password);
	if (ret == 0) {
		((OBSBasic *)this->parent())->OBSInit();
		this->close();
	} else {
		int ret = QMessageBox::critical(
			NULL, QTStr("Login.Title"), //QTStr("login failed"),
			QTStr("Login.Text"), //QTStr("login failed, check you net , username and password is correct"),
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		if (ret == QMessageBox::No) {
			this->close();
			exit(0);
		}
	}
	
	return;
}

void OBSBasicLogin::on_m_btnsignin_clicked() {
	QMessageBox::critical(NULL, QTStr("sign in"),
		QTStr("waiting code"),
		QMessageBox::Ok, QMessageBox::Ok);
}

int OBSBasicLogin::Login(const std::string& strUserName, const std::string & strPassword)
{
	CCurlHttpClient client;
	std::string strUrl = "http://www.baidu.com";
	std::string strPost;
	std::string response;

	int ret = client.Get(strUrl, response);

	return ret;
}
