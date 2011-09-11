#ifndef SqliteBase_hpp
#define SqliteBase_hpp

#include <string>
#include <iostream>
using namespace std;
#include <sqlite3.h>

#ifdef _WIN32
#define snprintf _snprintf
#pragma warning(disable:4996)
#endif

#define COPY_SQL(psrc) mSqlPtr = psrc;
#define FORMAT_SQL(...)  \
    snprintf(mSqlBuf, mSqlBufSize, __VA_ARGS__);\
    mSqlPtr = mSqlBuf;

namespace scx {

enum StepStatus
{
    StepBusy = SQLITE_BUSY,
    StepDone = SQLITE_DONE,
    StepError = SQLITE_ERROR,
    StepMisuse = SQLITE_MISUSE,
    StepRow = SQLITE_ROW
};

class SqliteBase
{
public:
    SqliteBase():
        mDbName(""),
        mSqlPtr(NULL),
        mSqlBuf(NULL),
        mSqlBufSize(0),
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
        ExecSql("PRAGMA foreign_keys=ON;");
    }

    void ExecSql()
    {
        ExecSql(mSqlPtr);
    }

    void ExecSql(const string &sql)
    {
        cout << sql << endl;
        sqlite3_exec(mDbConn, sql.c_str(), NULL, 0, 0);
    }

    void Prepare()
    {
        Prepare(mSqlPtr);
    }

    void Prepare(const string &sql)
    {
        sqlite3_prepare_v2(mDbConn, sql.c_str(), -1, &mStmt, 0);
    }

    StepStatus NextStep()
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

    int ColumnInt(int col)
    {
        return sqlite3_column_int(mStmt, col);
    }

    sqlite3_int64 ColumnInt64(int col)
    {
        return sqlite3_column_int64(mStmt, col);
    }

    double ColumnDouble(int col)
    {
        return sqlite3_column_double(mStmt, col);
    }

protected:
    string mDbName;
    const char* mSqlPtr;
    char* mSqlBuf;
    size_t mSqlBufSize;
    sqlite3* mDbConn;
    sqlite3_stmt* mStmt;
};

}

#endif // SqliteBase_hpp
