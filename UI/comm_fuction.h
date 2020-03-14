#ifndef __COMM_FUCTION_H__
#define __COMM_FUCTION_H__
#include <string>
#include "windows.h"

char *U8ToUnicode(const char *szU8);
char *UnicodeToU8(const wchar_t *wszString);
char *Utf8ToMultiBy(const char *utf8);
std::wstring StringToWString(const std::string &str);
std::string WStringToString(const std::wstring &wstr);
void sha_crypt(const char *szInput, int ilen, unsigned char *szOutput);
void getdatefromtime(time_t t, char * outtime/*YYYY-MM-DD*/);
int DOWNLOAD_FILE(const char *url, const char outfilename[FILENAME_MAX]);

#endif
