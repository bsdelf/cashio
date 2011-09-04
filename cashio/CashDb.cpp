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
    sqlite3_open(mDbName.c_str(), &mDbHandle);
    SetupPragma();
}

void CashDb::CloseDb()
{
    mDbName.clear();
    sqlite3_close(mDbHandle);
    mDbHandle = NULL;
}

void CashDb::InitDb()
{
    // tags table
    FORMAT_SQL(SQL_CREATE_TABLE_TAGS, TABLE_TAGS);
    ExecSql();
    // account table
    FORMAT_SQL(SQL_CREATE_TABLE_ACCOUNT, TABLE_ACCOUNT_MISC);
    ExecSql();
    // account-tag table
    FORMAT_SQL(SQL_CREATE_TABLE_ACCOUNT_TAG, TABLE_ACCOUNT_MISC_TAG);
    ExecSql();
}

void CashDb::ClearDb()
{
    // TODO: detect all tables, then remove them
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_TAGS);
    ExecSql();
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_ACCOUNT_MISC);
    ExecSql();
    FORMAT_SQL(SQL_DROP_TABLE, TABLE_ACCOUNT_MISC_TAG);
    ExecSql();
}

void CashDb::InsertTag(const string &tag)
{

}

void CashDb::DropTag(const string &tag)
{

}

void CashDb::UpdateTag(const string &oldTag, const string &newTag)
{

}

void CashDb::GetTags(TagVector &tags)
{
    tags.clear();
}

void CashDb::InsertAccountItem(const AccountItem &item)
{

}

void CashDb::DropAccountItem(const string &date)
{

}

void CashDb::UpdateAccountItem(const string &date, const AccountItem &item)
{

}

void CashDb::GetAccountItems(AccountVector &items)
{
    items.clear();
}

string CashDb::GetTime()
{
    return "";
}
