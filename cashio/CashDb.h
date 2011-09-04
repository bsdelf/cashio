#ifndef CashDb_H
#define CashDb_H

#include <vector>
#include <string>
using namespace std;
#include "SqliteBase.h"

struct AccountItem
{
    string date;
    int inout;
    double amount;
    vector<string> tags;
};

typedef vector<string> TagVector;
typedef vector<AccountItem> AccountVector;

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

    void InsertTag(const string& tag);
    void DropTag(const string& tag);
    void UpdateTag(const string& oldTag, const string& newTag);
    void GetTags(TagVector& tags);

    void InsertAccountItem(const AccountItem& item);
    void DropAccountItem(const string& date);
    void UpdateAccountItem(const string& date, const AccountItem& item);
    void GetAccountItems(AccountVector& items);

    string GetTime();
};

#endif // CashDb_H
