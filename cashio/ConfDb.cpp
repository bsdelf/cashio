#include "ConfDb.h"
#include "DbDef.h"

const char KEY_VERSION[] = "Version";

ConfDb::ConfDb()
{
}

ConfDb::~ConfDb()
{

}

string ConfDb::GetVersion()
{
    FORMAT_SQL(SQL_QUERY_INFO_VALUE, KEY_VERSION);
    Prepare();
    return (NextStep() == StepRow) ? ColumnString(0) : "";
}

void ConfDb::SetVersion(const string& ver)
{

}
