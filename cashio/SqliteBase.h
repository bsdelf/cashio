#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <string>
using namespace std;
#include <sqlite3.h>

#ifdef _WIN32
#define snprintf _snprintf
#pragma warning(disable:4996)
#endif

#define FORMAT_SQL(...) snprintf(mSqlBuf, SQL_BUF_SIZE, __VA_ARGS__)

class SqliteBase
{
public:
    SqliteBase():
        mDbName(""),
        mSqlBuf(NULL),
        mSqlBufLen(0),
        mDbHandle(NULL),
        mDbStmt(NULL)
    {
    }

    ~SqliteBase()
    {
    }

protected:
    void SetupPragma()
    {
        ExecSql("PRAGMA journal_mode=off;");
        ExecSql("PRAGMA synchronous=off;");
        ExecSql("PRAGMA cache_size=8000;");
    }

    void ExecSql()
    {
        ExecSql(mSqlBuf);
    }

    void ExecSql(const string &sql)
    {
        sqlite3_exec(mDbHandle, sql.c_str(), NULL, 0, 0);
    }

protected:
    string mDbName;
    char* mSqlBuf;
    size_t mSqlBufLen;
    sqlite3* mDbHandle;
    sqlite3_stmt* mDbStmt;
};

#endif // SQLITEHELPER_H
