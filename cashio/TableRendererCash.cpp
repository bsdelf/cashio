#include "TableRendererCash.h"
#include <iostream>
using namespace std;

TableRendererCash::TableRendererCash(QObject *parent) :
    QObject(parent),
    mHasNewRow(false)
{
    openDb("a.db");

    mCombDelegateInOut.addText("In");
    mCombDelegateInOut.addText("Out");
}

TableRendererCash::~TableRendererCash()
{

}

void TableRendererCash::openDb(const QString &path)
{
    mCashDb.OpenDb(path.toStdString());
    mCashDb.InitDb();
}

void TableRendererCash::closeDb()
{
    mCashDb.CloseDb();
}

void TableRendererCash::setupTable(QTableView *table)
{
    mPtrTable = table;

    mPtrTable->verticalHeader()->setVisible(true);
    mPtrTable->horizontalHeader()->setVisible(true);
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    mPtrTable->setAlternatingRowColors(true);
    mPtrTable->setItemDelegateForColumn(1, &mCombDelegateInOut);

    QStringList  list;
    list << tr("Date") << tr("In/Out") << tr("Amount") << tr("Tags");
    mModel.setHorizontalHeaderLabels(list);

    QList<QStandardItem*> rowList;
    QStandardItem* item;
    item = new QStandardItem("");
    rowList << item;
    item = new QStandardItem("Out");
    rowList << item;
    item = new QStandardItem("a");
    rowList << item;
    item = new QStandardItem("a");
    rowList << item;
    mModel.appendRow(rowList);
   // mModel.insertRow();
    mPtrTable->setModel(&mModel);
    mPtrTable->resizeColumnsToContents();
    mPtrTable->edit(mModel.index(0, 0));

    connect(&mModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelDataChanged(QStandardItem*)));

}

void TableRendererCash::unsetupTable()
{

}

void TableRendererCash::prepareNewRow()
{
    QList<QStandardItem*> row;
    row << new QStandardItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
    row << new QStandardItem("Out");
    row << new QStandardItem();
    row << new QStandardItem();

    if (mHasNewRow)
    {
        mModel.removeRow(0);
    }
    mModel.insertRow(0, row);
    mHasNewRow = true;


    mPtrTable->setModel(&mModel);
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);

    QModelIndex index = mModel.index(0, 1);
    mPtrTable->setCurrentIndex(index);
    mPtrTable->edit(index);
}

bool TableRendererCash::tryToSaveRows()
{
    mHasNewRow = false;
    for (int i = 0; i < mModel.columnCount(); ++i)
    {
        QStandardItem* item = mModel.item(0, i);
        if (item->text().isEmpty())
        {
            mModel.removeRow(0);
            return false;
        }
    }
    return true;
}

bool TableRendererCash::rmSelectedRows()
{
    if (mHasNewRow)
    {
        mModel.removeRow(0);
        mHasNewRow = false;
    }
    return true;
}

void TableRendererCash::slotModelDataChanged(QStandardItem * item)
{
    cout << "r:" << item->row() << " c:" << item->column() << endl;
}
