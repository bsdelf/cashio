#include "ConfDb.h"
#include "DbDef.h"

const int SQL_BUF_SIZE = 1024;

const char KEY_WND_X[] = "WND_X";
const char KEY_WND_Y[] = "WND_Y";
const char KEY_WND_WIDTH[] = "WND_WIDTH";
const char KEY_WND_HEIGHT[] = "WND_HEIGHT";
const char KEY_LAST_OPEN_PATH[] = "LAST_OPEN_PATH";

ConfDb::ConfDb()
{
    mSqlBuf = new char[SQL_BUF_SIZE];
    mSqlBufSize = SQL_BUF_SIZE;
}

ConfDb::~ConfDb()
{
    delete mSqlBuf;
}

void ConfDb::OpenDb(const string& dbFile, bool needInit)
{
    sqlite3_open(dbFile.c_str(), &mDbConn);
    SetupPragma();

    if (needInit) {
        ExecSql(SQL_CREATE_TABLE_CONF);

        Begin();
        FORMAT_SQL(SQL_INSERT_CONF_INT, KEY_WND_X, 0);
        ExecSql();
        FORMAT_SQL(SQL_INSERT_CONF_INT, KEY_WND_Y, 0);
        ExecSql();
        FORMAT_SQL(SQL_INSERT_CONF_INT, KEY_WND_WIDTH, 0);
        ExecSql();
        FORMAT_SQL(SQL_INSERT_CONF_INT, KEY_WND_HEIGHT, 0);
        ExecSql();
        FORMAT_SQL(SQL_INSERT_CONF_STR, KEY_LAST_OPEN_PATH, "");
        ExecSql();
        Commit();
    }
}

void ConfDb::CloseDb()
{
    sqlite3_close(mDbConn);
    mDbConn = NULL;
}

int ConfDb::GetWindowX()
{
    FORMAT_SQL(SQL_QUERY_CONF_VALUE, KEY_WND_X);
    Prepare();
    return (NextStep() == StepRow) ? ColumnInt(0) : 0;
}

int ConfDb::GetWindowY()
{
    FORMAT_SQL(SQL_QUERY_CONF_VALUE, KEY_WND_Y);
    Prepare();
    return (NextStep() == StepRow) ? ColumnInt(0) : 0;
}

int ConfDb::GetWindowWidth()
{
    FORMAT_SQL(SQL_QUERY_CONF_VALUE, KEY_WND_WIDTH);
    Prepare();
    return (NextStep() == StepRow) ? ColumnInt(0) : 0;
}

int ConfDb::GetWindowHeight()
{
    FORMAT_SQL(SQL_QUERY_CONF_VALUE, KEY_WND_HEIGHT);
    Prepare();
    return (NextStep() == StepRow) ? ColumnInt(0) : 0;
}

string ConfDb::GetLastOpenPath()
{
    FORMAT_SQL(SQL_QUERY_CONF_VALUE, KEY_LAST_OPEN_PATH);
    Prepare();
    return (NextStep() == StepRow) ? ColumnString(0) : "";
}

void ConfDb::SetWindowX(int x)
{
    FORMAT_SQL(SQL_UPDATE_CONF_INT,
               KEY_WND_X,
               x,
               KEY_WND_X);
    ExecSql();
}

void ConfDb::SetWindowY(int y)
{
    FORMAT_SQL(SQL_UPDATE_CONF_INT,
               KEY_WND_Y,
               y,
               KEY_WND_Y);
    ExecSql();
}

void ConfDb::SetWindowWidth(int w)
{
    FORMAT_SQL(SQL_UPDATE_CONF_INT,
               KEY_WND_WIDTH,
               w,
               KEY_WND_WIDTH);
    ExecSql();
}

void ConfDb::SetWindowHeight(int h)
{
    FORMAT_SQL(SQL_UPDATE_CONF_INT,
               KEY_WND_HEIGHT,
               h,
               KEY_WND_HEIGHT);
    ExecSql();
}

void ConfDb::SetLastOpenPath(const string& path)
{
    FORMAT_SQL(SQL_UPDATE_CONF_STR,
               KEY_LAST_OPEN_PATH,
               path.c_str(),
               KEY_LAST_OPEN_PATH);
    ExecSql();
}

bool ConfDb::HasKey(const string&)
{
    return true;
}
