#ifndef CONFDB_H
#define CONFDB_H

#include "SqliteBase.hpp"
using namespace scx;

class ConfDb: public SqliteBase
{
public:
    ConfDb();
    ~ConfDb();

    string GetVersion();
    void SetVersion(const string& ver);
};

#endif // CONFDB_H
