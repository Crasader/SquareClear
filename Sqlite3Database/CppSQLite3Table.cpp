#include "CppSQLite3Table.h"
#include "Library/sqlite/sqlite3.h"
#include "CppSQLite3.h"
#include "stdlib.h"

CppSQLite3Table::CppSQLite3Table()
{
	mnCols = 0;
	mnRows = 0;
	mnCurrentRow = 0;
	mpaszResults = 0;
}

CppSQLite3Table::CppSQLite3Table(const CppSQLite3Table &rTable)
{
	mnCols = rTable.mnCols;
	mnRows = rTable.mnRows;
	mnCurrentRow = rTable.mnCurrentRow;
	mpaszResults = rTable.mpaszResults;
	const_cast<CppSQLite3Table&>(rTable).mpaszResults = 0; //������ʱ������ԭ���ı���ֹ��ʧ�޸�  
}

CppSQLite3Table::CppSQLite3Table(char **paszResults, int nRows, int nCols)
{
	mpaszResults = paszResults; //����һ��һάָ�����飬��ʼ��һ����  
	mnCols = nCols;
	mnRows = nRows;
	mnCurrentRow = 0;
}

CppSQLite3Table::~CppSQLite3Table()
{
	finalize();
}

CppSQLite3Table& CppSQLite3Table::operator= (const CppSQLite3Table &rTable)
{
	finalize();

	mpaszResults = rTable.mpaszResults;
	const_cast<CppSQLite3Table &>(rTable).mpaszResults = 0;
	mnCols = rTable.mnCols;
	mnRows = rTable.mnRows;
	mnCurrentRow = rTable.mnCurrentRow;

	return *this;
}

void CppSQLite3Table::finalize()
{
	if (mpaszResults)
	{
		sqlite3_free_table(mpaszResults);  //���ÿ⺯�����ٱ�洢����  
		mpaszResults = 0;
	}
}

int CppSQLite3Table::NumOfFields()
{
	CheckResluts();

	return mnCols;
}

int CppSQLite3Table::NumOfRows()
{
	CheckResluts();

	return mnRows;
}

const char* CppSQLite3Table::NameOfField(int nField)
{
	CheckResluts();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw CppSQLite3Exception(CPPSQLITE_ERROR,
			"Invalid field index requested",
			DONT_DELETE_MSG);
	}

	return mpaszResults[nField]; //һλ�����ͷmnCols��Ԫ�ش�ŵ��Ǳ���ֶ����ƣ��洢����λ����mpaszResults[0,,,mnCols-1]��  
}

const char* CppSQLite3Table::ValueOfField(int nField)
{
	CheckResluts();

	if (nField < 0 || nField > mnCols - 1)
	{
		throw CppSQLite3Exception(CPPSQLITE_ERROR,
			"Invalid field index requested",
			DONT_DELETE_MSG);
	}

	//����Ҫ��ѯ�ĵ�ǰ������ֵ�����һλ�����е������±꣬�����һ��mnCols�ǵ�һ�д洢�����ֶ���  
	int nIndex = mnCurrentRow*mnCols + mnCols + nField;
	return mpaszResults[nIndex];
}

//�����ֶ�����������ĳһ�е�����  
const char* CppSQLite3Table::ValueOfField(const char *szField)
{
	CheckResluts();

	if (szField)
	{
		for (int nField = 0; nField < mnCols; nField++)
		{
			if (strcmp(szField, mpaszResults[nField]) == 0)
			{
				int nIndex = mnCurrentRow*mnCols + mnCols + nField;
				return mpaszResults[nIndex];
			}
		}
	}

	throw CppSQLite3Exception(CPPSQLITE_ERROR,
		"Invalid field name requested",
		DONT_DELETE_MSG);
}

bool CppSQLite3Table::FieldIsNull(int nField)
{
	CheckResluts();

	return (ValueOfField(nField) == 0);
}

bool CppSQLite3Table::FieldIsNull(const char* szField)
{
	CheckResluts();

	return (ValueOfField(szField) == 0);
}

//����Ļ�ȡ����������ֵ��������Ҫ�û������ݿ��еı���һ�����˽⣬֪����Щ�ֶδ洢����ʲô����  
//����ʹ�õ����ⲿ�������õ���ʽ  
bool CppSQLite3Table::GetIntField(int nField, int &rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//atoi()������C�⺯��������ֵ���ַ���ת��Ϊ����ֵ  
		rDest = atoi(ValueOfField(nField));
		return true;
	}
}

bool CppSQLite3Table::GetIntField(const char *szField, int &rDest)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atoi(ValueOfField(szField));
		return true;
	}
}

bool CppSQLite3Table::GetFloatField(int nField, double &rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		//C�⺯��������ֵ���ַ���ת��Ϊ������  
		rDest = atof(ValueOfField(nField));
		return true;
	}
}

bool CppSQLite3Table::GetFloatField(const char *szField, double &rDest)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDest = atof(ValueOfField(szField));
		return true;
	}
}

bool CppSQLite3Table::GetStringField(int nField, char *&rDest)
{
	if (FieldIsNull(nField))
	{
		return false;
	}
	else
	{
		rDest = const_cast<char *>(ValueOfField(nField));
		return true;
	}
}
bool CppSQLite3Table::GetStringField(const char *szField, char *&rDset)
{
	if (FieldIsNull(szField))
	{
		return false;
	}
	else
	{
		rDset = const_cast<char *>(ValueOfField(szField));
		return true;
	}
}

//��ÿһ����Ҫ��ȡ���ݵ�ʱ��Ҫ����Ҫ���ʵ���ֵ  
void CppSQLite3Table::SetRow(int nRow)
{
	CheckResluts();

	if (nRow < 0 || nRow > mnCols - 1)
	{
		throw CppSQLite3Exception(CPPSQLITE_ERROR,
			"Invalid row index requested",
			DONT_DELETE_MSG);
	}

	mnCurrentRow = nRow;
}

void CppSQLite3Table::CheckResluts()
{
	if (mpaszResults == 0)
	{
		throw CppSQLite3Exception(CPPSQLITE_ERROR,
			"Null Results pointer",
			DONT_DELETE_MSG);
	}
}