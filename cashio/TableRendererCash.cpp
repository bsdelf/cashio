#include "TableRendererCash.h"

TableRendererCash::TableRendererCash(QObject *parent) :
    QObject(parent)
{
    mCashDb.OpenDb("a.db");
    mCashDb.InitDb();
}

void TableRendererCash::setupTable(QTableView *table)
{
    mPtrTable = table;
}

void TableRendererCash::renderTable()
{
    mPtrTable->setModel(&mModel);
}
