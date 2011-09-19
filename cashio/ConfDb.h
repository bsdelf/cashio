#ifndef CONFDB_H
#define CONFDB_H

#include "SqliteBase.hpp"
using namespace scx;
#include <string>
using namespace std;

class ConfDb: public SqliteBase
{
public:
    ConfDb();
    ~ConfDb();

public:
    void OpenDb(const string& dbFile, bool needInit);
    void CloseDb();

    int GetWindowX();
    int GetWindowY();
    int GetWindowWidth();
    int GetWindowHeight();
    string GetLastOpenPath();

    void SetWindowX(int x);
    void SetWindowY(int y);
    void SetWindowWidth(int w);
    void SetWindowHeight(int h);
    void SetLastOpenPath(const string& path);

private:
    bool HasKey(const string& key);

};

#endif // CONFDB_H
