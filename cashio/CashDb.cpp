#include "CashDb.h"
#include <cstdio>
using namespace std;
#include "DbDef.h"

const int SQL_BUF_SIZE = 200;

CashDb::CashDb()
{
    mSqlBuf = new char[SQL_BUF_SIZE];
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
    FORMAT_SQL(SQL_CREATE_TABLE_TAGS, TABLE_TAGS);
    ExecSql();
    // account table
    FORMAT_SQL(SQL_CREATE_TABLE_ACCOUNT, TABLE_ACCOUNT);
    ExecSql();
    // account-tag table
    FORMAT_SQL(SQL_CREATE_TABLE_ACCOUNT_TAG, TABLE_ACCOUNT_TAG);
    ExecSql();
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

string CashDb::GetTime()
{
    Prepare(SQL_QUERY_DATE);
    return (Step() == StepRow) ? ColumnString(0) : "";
}
