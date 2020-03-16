#include "window-basic-login.hpp"
#include "./ui_obsbasiclogin.h"
#include "window-basic-main.hpp"
#include "CCurlHttpClient.h"
#include <qmessagebox.h>
#include "qt-wrappers.hpp"
#include "time.h"
#include "stdlib.h"
#include "windows.h"
#include "json11.hpp"
#include "mbedtls/sha1.h"
#include "comm_fuction.h"
#include "openssl/sha.h"
#include "CMyConfig.h"

OBSBasicLogin::OBSBasicLogin(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::OBSBasicLogin)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
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
	std::string strErrMsg;
	int ret = Login(username, password, strErrMsg);
	if (ret == 0) {
		OBSBasic *pBasic = ((OBSBasic *)this->parent());
		pBasic->SetUseInfo(account, strToken, userId, usertype);
		pBasic->OBSInit();
		this->close();
	} else {
		int ret = 0;
		if (strErrMsg.empty())
		{
			ret = QMessageBox::critical(
				NULL, QTStr("Login.Title"), //QTStr("login failed"),
				QTStr("Login.Text"), //QTStr("login failed, check you net , username and password is correct"),
				QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}
		else
		{
			ret = QMessageBox::critical(
				NULL,
				QTStr("Login.Title"), //QTStr("login failed"),
				QTStr(strErrMsg.c_str()), //QTStr("login failed, check you net , username and password is correct"),
				QMessageBox::Yes | QMessageBox::No,
				QMessageBox::Yes);
		}
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


int OBSBasicLogin::Login(const std::string& strUserName, const std::string & strPassword,std::string & strOutErrorMsg)
{
	CCurlHttpClient client;

	//"http://47.115.139.190:9001/live/api/teacher/login";
	std::string strUrl = CMyConfig::Instance()->GetLoginUrl();
	
	std::string strPost;
	std::string response;
	unsigned char szsha1pwd[1024]={0};
	int ilen = strPassword.length();
	sha_crypt(strPassword.c_str(), ilen, szsha1pwd);

	std::string strPwd = (char *)szsha1pwd;
	json11::Json jsPost;
	
	jsPost =
		json11::Json::object{{"account", strUserName},
				      {"password", strPwd}
	};

	strPost = jsPost.dump();
		
	std::wstring wpost = StringToWString(strPost);
	char *szwpost = UnicodeToU8(wpost.c_str());
	std::string spost = szwpost;
	int ret = client.Post(strUrl, spost, response);
	if (0 != ret)
	{
		return ret;
	}
	const char *str = response.c_str(); //U8ToUnicode(response.c_str());
	std::string strerrcode;
	json11::Json jsResult = json11::Json::parse(str, strerrcode);
   	ret = jsResult["code"].int_value();
	if (10000 == ret)
	{
		ret = 0;
		account = jsResult["data"]["account"].string_value();
		strToken = jsResult["data"]["token"].string_value();
		usertype = jsResult["data"]["type"].int_value();
		userId = jsResult["data"]["userId"].int_value();
	}
	else
	{
		strOutErrorMsg = jsResult["message"].string_value();
	}
	return ret;
}
