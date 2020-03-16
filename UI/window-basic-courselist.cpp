#include "window-basic-courselist.h"
#include "./ui_OBSBasicCourseList.h"
#include <qstandarditemmodel.h>
#include <qmessagebox.h>
#include "window-basic-main.hpp"
#include "CCurlHttpClient.h"
#include "json11.hpp"
#include "comm_fuction.h"
#include "time.h"
#include <QTextCodec>
#include "CMyConfig.h"

OBSBasicCourseList::OBSBasicCourseList(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::OBSBasicCourseList),
	  m_current(1),
	  m_usertype(0),
	  m_userId(0),
	  m_slm(NULL),
	  m_selectedItem(NULL)
{
	int m_usertype;
	int m_userId;
	int m_current;
	ui->setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint);
}

OBSBasicCourseList::~OBSBasicCourseList()
{
	delete ui;
}

void OBSBasicCourseList::OBSInit()
{
	InitCourseList();
	InitLoadCourseList();
}

void OBSBasicCourseList::on_listView_doubleClicked(const QModelIndex &index)
{
	//QMessageBox::critical(NULL, "tips", "doubleclicked", QMessageBox::Ok,
	//		      QMessageBox::Ok);
	QStandardItemModel *model = (QStandardItemModel *)ui->listView->model();
	m_selectedItem = model->itemFromIndex(index);
	if (!m_selectedItem) {
		return;
	}
	std::map<QStandardItem *, json11::Json>::iterator it =
		m_mapResult.find(m_selectedItem);
	if (it == m_mapResult.end()) {
		return;
	}
	int id = it->second["id"].int_value();
	json11::Json jsPost;
	jsPost =
		json11::Json::object{{"scheduleId", id}, {"token", m_strToken}};
	std::string strPost = jsPost.dump();

	std::wstring wpost = StringToWString(strPost);
	char *szwpost = UnicodeToU8(wpost.c_str());
	std::string spost = szwpost;
	CCurlHttpClient client;
	std::string strUrl = CMyConfig::Instance()->GetLoadCourseStreamUrl();
	std::string response;
	int ret = client.Post(strUrl, spost, response);
	if (0 != ret) {
		QMessageBox::critical(NULL, "tips", "获取推流失败", QMessageBox::Ok,
				      QMessageBox::Ok);
		return;
	}
	const char *str = response.c_str(); //U8ToUnicode(response.c_str());
	std::string strerrcode;
	json11::Json jsResult = json11::Json::parse(str, strerrcode);
	ret = jsResult["code"].int_value();
	if (10000 == ret) {
		std::string rtmp = jsResult["data"].string_value();
		const std::string strCode = "";
		OBSBasic *pBasic = (OBSBasic *)parent();
		pBasic->SetSettingStreaming(rtmp, strCode);
		pBasic->StartStreaming();
	} else {
		std::string message = jsResult["message"].string_value();
		QMessageBox::critical(NULL, "warn", message.c_str(),
				      QMessageBox::Ok, QMessageBox::Ok);
	}	
}

void OBSBasicCourseList::onClicked(QModelIndex index)
{
	//QMessageBox::critical(NULL, "tips", "clicked", QMessageBox::Ok,
	//		      QMessageBox::Ok);
	return;
}

int OBSBasicCourseList::InitLoadCourseList()
{
	CCurlHttpClient client;
	//"http://47.115.139.190:9001/live/api/teacher/getScheduleList";
	std::string strUrl = CMyConfig::Instance()->GetLoadCourseUrl();

	std::string strPost;
	std::string response;

	json11::Json jsPost;
	char szStartData[32] = {0};
	char szEndData[32] = {0};
	time_t starttime = time(NULL);
	time_t endtime = starttime + 60 * 24 * 3600;
	getdatefromtime(starttime, szStartData);
	getdatefromtime(endtime, szEndData);
	jsPost = json11::Json::object{{"current", m_current},
				      {"startDate", szStartData},
				      {"size", 10},
				      {"endDate", szEndData},
				      {"token", m_strToken}};

	strPost = jsPost.dump();
	
	std::wstring wpost = StringToWString(strPost);
	char *szwpost = UnicodeToU8(wpost.c_str());
	std::string spost = szwpost;
	int ret = client.Post(strUrl, spost, response);
	if (0 != ret) {
		return ret;
	}

	const char *str = response.c_str(); //U8ToUnicode(response.c_str());
	std::string strerrcode;
	json11::Json jsResult = json11::Json::parse(str, strerrcode);
	ret = jsResult["code"].int_value();
	
	if (10000 == ret) {
		ret = 0;
		const std::vector<json11::Json> &records =
			jsResult["data"]["records"].array_items();
		QListView *listview = ui->listView;
		if (m_slm == NULL) {
			m_slm = new QStandardItemModel(this);
		}

		//"http://47.115.139.190:9001/live";
		std::string url = CMyConfig::Instance()->GetLoadImgUrl();
		m_current = m_current + records.size();
		for (int index = 0; index < records.size(); index++) {
			QStandardItem *s1;
			std::string coursename =
				records[index]["course"]["courseName"]
					.string_value();
			std::string chapter =
				records[index]["chapter"]["chapterName"]
					.string_value();
			std::string name = coursename + "-" + chapter;
			std::string bannerImg =
				records[index]["course"]["bannerImg"]
					.string_value();
			std::string strimgpath;
			
			GetModuleFileDir(strimgpath);
			strimgpath += bannerImg.substr(1, bannerImg.length());
			//const char *path =
			//  "D:\\code\\work\\obs-studio\\obs-studio\\UI\\build-2-Desktop_Qt_5_14_1_MSVC2017_32bit-Debug\\1.png";
			std::string doloadurl = url + bannerImg;
		
			DOWNLOAD_FILE(doloadurl.c_str(), strimgpath.c_str());
			
			s1 = new QStandardItem(QIcon(strimgpath.c_str()),
					       name.c_str());
			m_mapResult.insert(std::make_pair(s1, records[index]));
			m_slm->appendRow(s1);
		}
	} else {
		//strOutErrorMsg = jsResult["message"].string_value();
	}
	return ret;
}

void OBSBasicCourseList::InitCourseList()
{
	QListView *listview = ui->listView;
	m_vscrollBar = listview->verticalScrollBar();

	listview->setViewMode(QListView::IconMode);
	listview->setMovement(QListView::Free);
	listview->setIconSize(QSize(100, 100));
	listview->setGridSize(QSize(150, 100));
	//listview->setGeometry(0,0,480,272);
	listview->setResizeMode(QListView::Fixed);
	listview->setLayoutMode(QListView::SinglePass);

	m_slm = new QStandardItemModel(this);
	listview->setModel(m_slm);

	connect(listview, SIGNAL(clicked(QModelIndex)), this,
		SLOT(onClicked(QModelIndex)));
	connect(m_vscrollBar, SIGNAL(valueChanged(int)), this,
		SLOT(onSliderChanged(int)));
}

void OBSBasicCourseList::SetUseInfo(const std::string &account,
				    const std::string &strToken, int userId,
				    int userType)
{
	m_account = account;
	m_strToken = strToken;
	m_userId = userId;
	m_usertype = userType;
}

void OBSBasicCourseList::onSliderChanged(int p)
{
	QListView *listview = ui->listView;

	if (p == m_vscrollBar->maximum()) {
		InitLoadCourseList();
	}
	// 2
}
