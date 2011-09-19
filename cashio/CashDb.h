#ifndef CashDb_H
#define CashDb_H

#include <vector>
#include <string>
using namespace std;
#include "SqliteBase.hpp"
using namespace scx;

struct Tag
{
    string name;
    int color;

    Tag() {}

    Tag(const Tag& tag):
        name(tag.name), color(tag.color) { }

    Tag(const string& n, const int& c):
        name(n), color(c) { }
};

struct Row
{
    string date;
    string io;
    double amount;
    vector<Tag> tags;
    string note;

    Row() {}

    Row(const string& _date, const string& _io, const double _amount, const string& _note):
        date(_date), io(_io), amount(_amount), note(_note) { }
};

typedef vector<Tag> TagVector;
typedef vector<Row*> RowPtrVector;
typedef vector<string> UuidVector;

class CashDb: public SqliteBase
{
public:
    CashDb();
    ~CashDb();

public:
    void OpenDb(const string& path);
    void CloseDb();
    void InitDb();
    void ClearDb();

    int GetVersion();
    void UpgradeDb();

    void InsertTag(const Tag& tag);
    void DeleteTag(const string& tagName);
    void UpdateTag(const string& oldTagName, const Tag& newTag);
    void GetTags(TagVector& tags);
    bool HasTag(const string& tagName);

    void InsertRow(const string& uuid, const Row* item);
    void DeleteRow(const string& uuid);
    void UpdateRow(const string& uuid, const Row& row, const UuidVector& tagUuids, TagVector& newTags);
    void QueryAllRows(UuidVector& range);
    void QueryRows(const string& query, UuidVector& range);
    void GetRows(const UuidVector& range, RowPtrVector &rows);
    bool HasRow(const string& uuid);

    string GetTime();
};

#endif // CashDb_H
