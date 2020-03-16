#include "window-basic-chartroom.h"
#include "./ui_obsbasicchartroom.h"
#include "windows.h"

OBSBasicChartRoom::OBSBasicChartRoom(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::OBSBasicChartRoom),
	  m_usertype(0),
	  m_userId(0),
	  m_messageId(0)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint);
}

OBSBasicChartRoom::~OBSBasicChartRoom()
{
	delete ui;
}

void OBSBasicChartRoom::SetUseInfo(const std::string &account,
				   const std::string &strToken, int userId,
				   int userType)
{
	m_account = account;
	m_strToken = strToken;
	m_userId = userId;
	m_usertype = userType;
}

DWORD WINAPI ThreadFunc(LPVOID lpVoid)
{

	return 0;
}

int OBSBasicChartRoom::InitLoadMessage()
{
	CreateThread(NULL, 0, ThreadFunc, this, 0, 0);
	return 0;
}
