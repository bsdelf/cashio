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

enum StepStatus
{
    StepBusy = SQLITE_BUSY,
    StepDone = SQLITE_DONE,
    StepError = SQLITE_ERROR,
    StepMisuse = SQLITE_MISUSE,
    StepRow = SQLITE_ROW,
};

class SqliteBase
{
public:
    SqliteBase():
        mDbName(""),
        mSqlBuf(NULL),
        mSqlBufLen(0),
        mDbConn(NULL),
        mStmt(NULL)
    {
    }

    ~SqliteBase()
    {
        if (mStmt != NULL)
        {
            sqlite3_finalize(mStmt);
        }
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
        sqlite3_exec(mDbConn, sql.c_str(), NULL, 0, 0);
    }

    void Prepare(const string &sql)
    {
        sqlite3_prepare_v2(mDbConn, sql.c_str(), -1, &mStmt, 0);
    }

    StepStatus Step()
    {
        return (StepStatus)sqlite3_step(mStmt);
    }

    int ColumnBytes(int col)
    {
        return sqlite3_column_bytes(mStmt, col);
    }

    string ColumnString(int col)
    {
        return string((const char*)sqlite3_column_text(mStmt, col));
    }

protected:
    string mDbName;
    char* mSqlBuf;
    size_t mSqlBufLen;
    sqlite3* mDbConn;
    sqlite3_stmt* mStmt;
};

#endif // SQLITEHELPER_H
