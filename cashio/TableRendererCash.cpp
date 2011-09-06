#include "TableHolderCash.h"
#include <iostream>
using namespace std;

TableHolderCash::TableHolderCash(QObject *parent) :
    QObject(parent),
    mHasNewRow(false)
{
    openDb("a.db");

    mCombDelegateInOut.addText("In");
    mCombDelegateInOut.addText("Out");
}

TableHolderCash::~TableHolderCash()
{

}

void TableHolderCash::openDb(const QString &path)
{
    mCashDb.OpenDb(path.toStdString());
    mCashDb.InitDb();
}

void TableHolderCash::closeDb()
{
    mCashDb.CloseDb();
}

void TableHolderCash::setupTable(QTableView *table)
{
    mPtrTable = table;

    mPtrTable->verticalHeader()->setVisible(true);
    mPtrTable->horizontalHeader()->setVisible(true);
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    mPtrTable->setAlternatingRowColors(true);
    mPtrTable->setItemDelegateForColumn(1, &mCombDelegateInOut);

    QStringList  list;
    list << tr("Date") << tr("IO") << tr("Amount") << tr("Tags") << tr("Note");
    mModel.setHorizontalHeaderLabels(list);

    QList<QStandardItem*> rowList;
    rowList << new QStandardItem("");
    rowList << new QStandardItem("Out");
    rowList << new QStandardItem("100");
    rowList << new QStandardItem("tag");
    rowList << new QStandardItem("");
    mModel.appendRow(rowList);
   // mModel.insertRow();
    mPtrTable->setModel(&mModel);
    mPtrTable->resizeColumnsToContents();
    mPtrTable->edit(mModel.index(0, 0));

    connect(&mModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelDataChanged(QStandardItem*)));

}

void TableHolderCash::unsetupTable()
{

}

void TableHolderCash::prepareNewRow()
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

bool TableHolderCash::tryToSaveRows()
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

bool TableHolderCash::rmSelectedRows()
{
    if (mHasNewRow)
    {
        mModel.removeRow(0);
        mHasNewRow = false;
    }
    return true;
}

void TableHolderCash::slotModelDataChanged(QStandardItem * item)
{
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    cout << "r:" << item->row() << " c:" << item->column() << endl;
}
