#include "CppSQLite3Query.h"
#include "CppSQLite3.h"
#include "CppSQLite3Statement.h"
#include "CppSQLite3DB.h"
#include "CppSQLite3Table.h"

CppSQLite3DB::CppSQLite3DB()
{
	mpDB = 0;
}

CppSQLite3DB::CppSQLite3DB(const CppSQLite3DB &rDB)
{
	mpDB = rDB.mpDB;
}

CppSQLite3DB::~CppSQLite3DB()
{
	Close();
}

CppSQLite3DB& CppSQLite3DB::operator =(const CppSQLite3DB &rDB)
{
	mpDB = rDB.mpDB;
	return *this;
}

void CppSQLite3DB::CheckDB()
{
	if (!mpDB)
	{
		throw CppSQLite3Exception(CPPSQLITE_ERROR,
			"Database not open",
			DONT_DELETE_MSG);
	}
}

sqlite3_stmt* CppSQLite3DB::Compile(const char *szSQL)
{
	CheckDB();

	const char *szTail = 0;
	sqlite3_stmt *pStmt;

	int nRet = sqlite3_prepare(mpDB, szSQL, -1, &pStmt, &szTail);

	if (nRet != SQLITE_OK)
	{
		const char *szError = sqlite3_errmsg(mpDB);
		throw CppSQLite3Exception(nRet, szError, DONT_DELETE_MSG);
	}

	return pStmt;
}

void CppSQLite3DB::Open(const char *szFileName)
{
	int nRet = sqlite3_open(szFileName, &mpDB);
	if (nRet != SQLITE_OK)
	{
		const char *szError = sqlite3_errmsg(mpDB);
		throw CppSQLite3Exception(nRet, szError, DONT_DELETE_MSG);
	}
}

void CppSQLite3DB::Close()
{
	if (mpDB)
	{
		if (sqlite3_close(mpDB) == SQLITE_OK)
		{
			mpDB = 0; //һ���ر����ݿ�ָ�룬Ҫ��Ϊ0����ֹ��ιرճ���  
		}
		else
		{
			throw CppSQLite3Exception(CPPSQLITE_ERROR,
				"Unable to close database",
				DONT_DELETE_MSG);
		}
	}
}

int CppSQLite3DB::ExecDML(const char *szSQL)
{
	CheckDB();

	char* szError = 0;

	int nRet = sqlite3_exec(mpDB, szSQL, 0, 0, &szError);

	if (nRet == SQLITE_OK)
	{
		return sqlite3_changes(mpDB);  //�������ִ��Ӱ�������  
	}
	else
	{
		throw CppSQLite3Exception(nRet, szError, DONT_DELETE_MSG);
	}
}

CppSQLite3Query CppSQLite3DB::ExecQuery(const char *szSQL)
{
	CheckDB();

	//����һ��ָ���������ʱ�����洢�����ݸ�CppSQLite3Query��  
	//�����ʱsqlite3_stmt*������Զ���ʧ�����ֻ��һ�ݱ�����CppSQLite3Query��  
	sqlite3_stmt *pStmt = Compile(szSQL);

	int nRet = sqlite3_step(pStmt);

	if (nRet == SQLITE_DONE) //���������ѯû�з��ؽ��  
	{
		return CppSQLite3Query(mpDB, pStmt, true); //���Խ��������ֶ�����Ϊtrue�����������ѯ���ĩβ��  
	}
	else if (nRet == SQLITE_ROW) //�����ѯ��������һ�м�¼  
	{
		return CppSQLite3Query(mpDB, pStmt, false); //false����û�е����ѯ���ĩβ  
	}
	else
	{
		nRet = sqlite3_finalize(pStmt);
		const char *szError = sqlite3_errmsg(mpDB);
		throw CppSQLite3Exception(nRet, szError, DONT_DELETE_MSG);
	}
}

CppSQLite3Table CppSQLite3DB::GetTable(const char *szSQL)
{
	CheckDB();

	char* szError = 0;
	char** paszResults = 0;
	int nRet;
	int nRows(0);
	int nCols(0);

	nRet = sqlite3_get_table(mpDB, szSQL, &paszResults, &nRows, &nCols, &szError);

	if (nRet == SQLITE_OK)
	{
		return CppSQLite3Table(paszResults, nRows, nCols);
	}
	else
	{
		throw CppSQLite3Exception(nRet, szError, DONT_DELETE_MSG);
	}
}

CppSQLite3Statement CppSQLite3DB::CompileStatement(const char *szSQL)
{
	CheckDB();

	sqlite3_stmt *pStmt = Compile(szSQL);
	return CppSQLite3Statement(mpDB, pStmt);
}