#ifndef CashDb_H
#define CashDb_H

#include <vector>
#include <string>
using namespace std;
#include "SqliteBase.h"

struct Tag
{
    string name;
    int color;
};

struct Row
{
    string date;
    string io;
    double amount;
    vector<Tag> tags;
    string note;
};

typedef vector<Tag> TagVector;
typedef vector<Row*> RowVector;
typedef vector<string> DateVector;

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

    void InsertTag(const Tag& tag);
    void DropTag(const string& tagName);
    void UpdateTag(const string& tagName, const Tag& newTag);
    void GetTags(TagVector& tags);
    bool HasTag(const string& tagName);

    void InsertRow(const Row& item);
    void DropRow(const string& date);
    void UpdateRow(const string& date, const Row& row);
    void QueryAllRows(DateVector& range);
    void QueryRows(const string& query, DateVector& range);
    void GetRows(const DateVector& range, RowVector &rows);
    bool HasRow(const string& date);

    string GetTime();
};

#endif // CashDb_H
