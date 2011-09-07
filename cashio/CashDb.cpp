#include "CashDb.h"
#include <cstdio>
using namespace std;
#include "DbDef.h"

const int SQL_BUF_SIZE = 500;

CashDb::CashDb()
{
    mSqlBuf = new char[SQL_BUF_SIZE];
    mSqlBufSize = SQL_BUF_SIZE;
}

CashDb::~CashDb()
{
    if (!mDbName.empty())
    {
        CloseDb();
    }

    delete mSqlBuf;
}

void CashDb::OpenDb(const string &path)
{
    mDbName = path;
    sqlite3_open(mDbName.c_str(), &mDbConn);
    SetupPragma();
}

void CashDb::CloseDb()
{
    mDbName.clear();
    sqlite3_close(mDbConn);
    mDbConn = NULL;
}

void CashDb::InitDb()
{
    // tags table
    ExecSql(SQL_CREATE_TABLE_TAGS);
    // account table
    ExecSql(SQL_CREATE_TABLE_ACCOUNT);
    // account-tag table
    ExecSql(SQL_CREATE_TABLE_ACCOUNT_TAG);
}

void CashDb::ClearDb()
{
    // TODO: detect all tables, then remove them
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_TAGS);
    ExecSql();
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_ACCOUNT);
    ExecSql();
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_ACCOUNT_TAG);
    ExecSql();
}

void CashDb::InsertTag(const Tag &tag)
{

}

void CashDb::DropTag(const string &tagName)
{

}

void CashDb::UpdateTag(const string &tagName, const Tag &newTag)
{

}

void CashDb::GetTags(TagVector &tags)
{
    tags.clear();
}

bool CashDb::HasTag(const string &tagName)
{
    FORMAT_SQL(SQL_QUERY_HAS_TAG, tagName.c_str());
    Prepare();
    return (NextStep() == StepRow) ? true : false;
}

void CashDb::InsertRow(const Row &item)
{

}

void CashDb::DropRow(const string &date)
{

}

void CashDb::UpdateRow(const string &date, const Row &row)
{

}

void CashDb::QueryRows(const string& query, DateVector& range)
{

}

void CashDb::GetRows(const DateVector& range, RowVector &rows)
{
    rows.clear();
    for (size_t i = 0; i < range.size(); ++i)
    {

    }
}

bool CashDb::HasRow(const string &date)
{
    FORMAT_SQL(SQL_QUERY_HAS_ACCOUNT, date.c_str());
    Prepare();
    return (NextStep() == StepRow) ? true : false;
}

string CashDb::GetTime()
{
    Prepare(SQL_QUERY_DATE);
    return (NextStep() == StepRow) ? ColumnString(0) : "";
}
