#include "comm_fuction.h"
#include <string>
#include "windows.h"
#include "openssl/sha.h"
#include "time.h"
#include "curl/curl.h"
#include <io.h>

char *U8ToUnicode(const char *szU8)
{
	//UTF8 to Unicode
	//预转换，得到所需空间的大小
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8),
					   NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t *wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString,
			      wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';

	char *m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString),
				      NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), m_char,
			    len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

char *UnicodeToU8(const wchar_t *wszString)
{
	// unicode to UTF8
	//预转换，得到所需空间的大小，这次用的函数和上面名字相反
	int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString,
					  wcslen(wszString), NULL, 0, NULL,
					  NULL);
	//同上，分配空间要给'\0'留个空间
	//UTF8虽然是Unicode的压缩形式，但也是多字节字符串，所以可以以char的形式保存
	char *szU8 = new char[u8Len + 1];
	//转换
	//unicode版对应的strlen是wcslen
	::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8,
			      u8Len, NULL, NULL);
	//最后加上'\0'
	szU8[u8Len] = '\0';
	return szU8;
}

std::wstring StringToWString(const std::string &str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

std::string WStringToString(const std::wstring &wstr)
{
	std::string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(),
					  nLen, (LPSTR)str.c_str(), nLen, NULL,
					  NULL);
	if (nResult == 0) {
		return "";
	}
	return str;
}

//utf8转为多字节
char * Utf8ToMultiBy(const char *utf8)
{
	int size = 0;
	char *multi;
	size = MultiByteToWideChar(CP_UTF8, NULL, utf8, -1, NULL, 0);
	wchar_t *buff = NULL;
	buff = (wchar_t *)malloc(sizeof(wchar_t) * (size + 1));
	if (!buff) {
		return 0;
	}
	wmemset(buff, 0, size + 1);
	MultiByteToWideChar(CP_ACP, NULL, utf8, -1, buff, size);
	int len = 0;
	len = WideCharToMultiByte(CP_ACP, NULL, buff, size, NULL, 0, NULL,
				  NULL);
	multi = NULL;
	multi = (char *)malloc(sizeof(char) * (len + 1));
	if (!multi) {
		free(buff);
		return 0;
	}
	memset(multi, 0, len + 1);
	WideCharToMultiByte(CP_ACP, NULL, buff, size, multi, len, NULL, NULL);
	free(buff);
	return multi;
}

void sha_crypt(const char *szInput, int ilen, unsigned char * szOutput)
{
	SHA_CTX ctx;
	unsigned char szSha1[256] = {0};
	SHA1_Init(&ctx);
	SHA1_Update(&ctx, (const void *)szInput, ilen);
	SHA1_Final(szSha1, &ctx);

	unsigned char szChar[3] = {0};
	for (int index = 0, pos = 0; index < 20; index++, pos += 2)
	{
		sprintf((char *)szChar, "%02x", szSha1[index]);
		szOutput[pos] = szChar[0];
		szOutput[pos  + 1] = szChar[1];
 	}
	return;
}

void getdatefromtime(time_t t, char *outtime /*YYYY-MM-DD*/)
{
	//获取本地时间
	tm *t_tm = localtime(&t);
	sprintf(outtime, "%04d-%02d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1,
		t_tm->tm_mday);
	return;
}

/************************************************************************/
/*    create by: mengxiaoxin   date:2014/12/9                           */
/************************************************************************/

/*  libcurl write callback function */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

/*			
			   Function:   libcurl connection initialization  download  file
			 Parameters:   (const char* url, const char outfilename[FILENAME_MAX])
			        url:   要下载文件的url地址
		    outfilename:   下载文件指定的文件名
*/
int DOWNLOAD_FILE(const char *url, const char outfilename[FILENAME_MAX])
{
	CURL *curl;
	FILE *fp;
	CURLcode res;

	if (0 == access(outfilename, 0))
	{
		return 0;
	}
	/*   调用curl_global_init()初始化libcurl  */
	res = curl_global_init(CURL_GLOBAL_ALL);
	if (CURLE_OK != res) {
		printf("init libcurl failed.");
		curl_global_cleanup();
		return -1;
	}
	/*  调用curl_easy_init()函数得到 easy interface型指针  */
	curl = curl_easy_init();
	if (curl) {

		fopen_s(&fp, outfilename, "wb");

		/*  调用curl_easy_setopt()设置传输选项 */
		res = curl_easy_setopt(curl, CURLOPT_URL, url);
		if (res != CURLE_OK) {
			fclose(fp);
			curl_easy_cleanup(curl);
			return -1;
		}
		/*  根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务  */
		res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		if (res != CURLE_OK) {
			fclose(fp);
			curl_easy_cleanup(curl);
			return -1;
		}
		/*  根据curl_easy_setopt()设置的传输选项，实现回调函数以完成用户特定任务  */
		res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		if (res != CURLE_OK) {
			fclose(fp);
			curl_easy_cleanup(curl);
			return -1;
		}

		res = curl_easy_perform(
			curl); // 调用curl_easy_perform()函数完成传输任务
		fclose(fp);
		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			return -1;
		}

		/* always cleanup */
		curl_easy_cleanup(curl); // 调用curl_easy_cleanup()释放内存
	}
	curl_global_cleanup();
	return 0;
}
