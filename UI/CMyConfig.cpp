#include "CMyConfig.h"
#include "windows.h"
#include "comm_fuction.h"

CMyConfig::CMyConfig()
{
	m_per_loadcourse_size = 10;
	m_login_url = "http://47.115.139.190:9001/live/api/teacher/login";
	m_load_course_url = "http://47.115.139.190:9001/live/api/teacher/getScheduleList";
	m_load_img_url = "http://47.115.139.190:9001/live";
	m_load_course_stream_url = "http://47.115.139.190:9001/live/api/teacher/getLiveURL";
}

CMyConfig::~CMyConfig()
{
}

CMyConfig *CMyConfig::Instance()
{
	static CMyConfig config;
	return &config;
}

int CMyConfig::LoadConfig()
{
	char szLoginUrl[MAX_PATH + 1] = {0};
	std::string configfile;
	GetModuleFileDir(configfile);
	configfile += "myconfig.ini";

	GetPrivateProfileStringA("Login", "url", "default", szLoginUrl, MAX_PATH, configfile.c_str());

	char szLoadCourseUrl[MAX_PATH + 1] = {0};
	GetPrivateProfileStringA("Course", "loadurl", "default", szLoadCourseUrl,
				 MAX_PATH, configfile.c_str());

	char szLoadCourseStreamUrl[MAX_PATH + 1] = {0};
	GetPrivateProfileStringA("Course", "loadStreamUrl", "default",
				 szLoadCourseStreamUrl, MAX_PATH,
				 configfile.c_str());

	char szLoadImgUrl[MAX_PATH + 1] = {0};
	GetPrivateProfileStringA("Course", "loadImgUrl", "default",
				 szLoadImgUrl, MAX_PATH,
				 configfile.c_str());

	m_per_loadcourse_size = GetPrivateProfileIntA("Course", "perLoadSize", 10,
						   configfile.c_str());
	m_login_url = szLoginUrl;
	m_load_course_url = szLoadCourseUrl;
	m_load_course_stream_url = szLoadCourseStreamUrl;
	m_load_img_url = szLoadImgUrl;

	return 0;
}

int CMyConfig::GetPerLoadCourseSize()
{
	return m_per_loadcourse_size;
}

const std::string CMyConfig::GetLoginUrl()
{
	return m_login_url;
}

const std::string CMyConfig::GetLoadCourseUrl()
{
	return m_load_course_url;
}

const std::string CMyConfig::GetLoadImgUrl()
{
	return m_load_img_url;
}

const std::string CMyConfig::GetLoadCourseStreamUrl()
{
	return m_load_course_stream_url;
}
