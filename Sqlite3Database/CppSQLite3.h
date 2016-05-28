#pragma once  
#include <cstdio>  
#include <cstring>  
#include "Library/sqlite/sqlite3.h"  

#define CPPSQLITE_ERROR 1000  //����궨����Ϊ�����ֿ⺯���ж���Ĵ�����룬ר�����Լ������е��쳣��ʾ 
static const bool DONT_DELETE_MSG = false;
class CppSQLite3Exception
{
private:
	int mnErrCode;
	char *mpszErrMessage;

public:
	CppSQLite3Exception(const int nErrNode,
		const char *szErrMess,
		bool bDeleteMess);
	CppSQLite3Exception(const CppSQLite3Exception &e);
	~CppSQLite3Exception();

	const int ErrorCode() { return mnErrCode; }
	const char *ErrorMessage() { return mpszErrMessage; }

	static const char* ErrorCodeAsString(const int nErrCode);
};