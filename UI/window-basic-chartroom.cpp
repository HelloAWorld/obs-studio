#include "window-basic-chartroom.h"
#include "./ui_obsbasicchartroom.h"

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

int OBSBasicChartRoom::InitLoadMessage() {
	return 0;
}
