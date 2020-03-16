#pragma once
#include <string>

class CMyConfig {
protected:
	CMyConfig();

public:
	~CMyConfig();

	static CMyConfig *Instance();

	int LoadConfig();

	int GetPerLoadCourseSize();
	const std::string GetLoginUrl();
	const std::string GetLoadCourseUrl();
	const std::string GetLoadImgUrl();
	const std::string GetLoadCourseStreamUrl();

private:
	int m_per_loadcourse_size;
	std::string m_login_url;
	std::string m_load_course_url;
	std::string m_load_img_url;
	std::string m_load_course_stream_url;
};
