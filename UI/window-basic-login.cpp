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
	Sleep(1 * 3000);
	CCurlHttpClient client;
	std::string strUrl = "http://www.baidu.com";
	std::string strPost;
	std::string response;

	int ret = client.Post(strUrl, strPost, response);
	
	if (ret == 0) {
		((OBSBasic *)this->parent())->OBSInit();
		this->close();	
	} else {
		int ret = QMessageBox::critical(
			NULL, QTStr("Login.Title"), //QTStr("login failed"),
			QTStr("Login.Text"),//QTStr("login failed, check you net , username and password is correct"),
				      QMessageBox::Yes | QMessageBox::No,
				      QMessageBox::Yes);
		if (ret == QMessageBox::No)
		{
			this->close();
			exit(0);
		}
	}
	return;
}
