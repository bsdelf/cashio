#include "TableHolderCash.h"
#include <iostream>
using namespace std;

TableHolderCash::TableHolderCash(QObject *parent) :
    QObject(parent),
    mHasNewRecord(false),
    mHasInvaildCell(false)
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

    DateVector range;
    mCashDb.QueryAllRows(range);
    mCashDb.GetRows(range, mRowVector);
    cout << mRowVector.size() << endl;
    for (size_t i = 0; i < mRowVector.size(); ++i)
    {
        Row* row = mRowVector[i];
        QList<QStandardItem*> rowList;
        rowList << new QStandardItem(QString::fromStdString(row->date));
        rowList << new QStandardItem(QString::fromUtf8(row->io.c_str()));
        rowList << new QStandardItem(QString::number(row->amount));
        rowList << new QStandardItem(""); // no tag now
        rowList << new QStandardItem(QString::fromUtf8(row->note.c_str()));
        mModel.insertRow(0, rowList);
    }

    mPtrTable->setModel(&mModel);
    mPtrTable->resizeColumnsToContents();
    QModelIndex index = mModel.index(0, 0);
    mPtrTable->setCurrentIndex(index);
    mPtrTable->edit(index);

    mPtrTable->setItemDelegateForColumn(ColumnDate, &mColorfulCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnAmount, &mColorfulCellDelegate);

    mColorfulCellDelegate.setCellColor(QColor(255, 48, 48));

    connect(&mModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelDataChanged(QStandardItem*)));

}

void TableHolderCash::unsetupTable()
{

}

void TableHolderCash::prepareNewRow()
{
    if (hasInvaildCell())
        return;

    QList<QStandardItem*> row;
    row << new QStandardItem(QString::fromStdString(mCashDb.GetTime()));
    row << new QStandardItem("Out");
    row << new QStandardItem();
    row << new QStandardItem();

    if (mHasNewRecord)
    {
        mModel.removeRow(0);
    }
    mModel.insertRow(0, row);
    mHasNewRecord = true;

    mPtrTable->setModel(&mModel);
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);

    QModelIndex index = mModel.index(0, ColumnAmount);
    mPtrTable->setCurrentIndex(index);
    mPtrTable->edit(index);
}

bool TableHolderCash::tryToSaveRows()
{
    mHasNewRecord = false;
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
    if (mHasNewRecord)
    {
        mModel.removeRow(0);
        mHasNewRecord = false;
    }
    return true;
}

void TableHolderCash::slotModelDataChanged(QStandardItem * item)
{
    // check whether the cell is vaild
    bool cellIsvaild = true;
    QModelIndex index = item->index();
    QString cellValue(mModel.data(index).toString());

    switch (index.column())
    {
    case ColumnDate:
        cellIsvaild = QDateTime::fromString(cellValue, "yyyy-MM-dd HH:mm:ss.zzz").isValid();
        break;

    case ColumnAmount:
        cellValue.toDouble(&cellIsvaild);
        break;
    }
    mHasInvaildCell = !cellIsvaild;

    if (cellIsvaild)
        mColorfulCellDelegate.removeIndex(index);
    else
        mColorfulCellDelegate.insertIndex(index);

    if (cellIsvaild)
    {
        if (mHasNewRecord)
            syncNewRecord();
        else
            updateRecord(index);
    }
    // resize
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    cout << "r:" << item->row() << " c:" << item->column() << endl;
}

bool TableHolderCash::hasInvaildCell()
{
    if (!mHasInvaildCell)
        return false;

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Error"));
    msgBox.setText(tr("Please correct the invaild cell first!"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    return true;
}

void TableHolderCash::syncNewRecord()
{
    if (!mHasNewRecord)
        return;
    cout << "sync" << endl;

    Row row;
    row.date = mModel.data(mModel.index(0, ColumnDate)).toString().toStdString();
    row.io = mModel.data(mModel.index(0, ColumnIO)).toString().toStdString();
    row.amount = mModel.data(mModel.index(0, ColumnAmount)).toDouble();
    QStringList tags = mModel.data(mModel.index(0, ColumnTag)).toString().split(QRegExp("\\s+"));
    row.tags.resize(tags.size());
    for(int i = 0; i< row.tags.size(); ++i)
    {
        row.tags[i] = tags[i].toStdString();
        cout << "tag" << i << ":" << row.tags[i] << endl;
    }
    row.note = mModel.data(mModel.index(0, ColumnNote)).toString().toStdString();

    cout << "date:" << row.date << endl;
    cout << "io:" << row.io << endl;
    cout << "amout:" << row.amount << endl;
    cout << "note:" << row.note << endl;

    mCashDb.InsertRow(row);
    mHasNewRecord = false;
}

void TableHolderCash::updateRecord(const QModelIndex &index)
{
    Row row;
    row.date = mModel.data(mModel.index(index.row(), ColumnDate)).toString().toStdString();
    row.io = mModel.data(mModel.index(index.row(), ColumnIO)).toString().toUtf8().data();
    row.amount = mModel.data(mModel.index(index.row(), ColumnAmount)).toDouble();
    QStringList tags = mModel.data(mModel.index(index.row(), ColumnTag)).toString().split(QRegExp("\\s+"));
    row.tags.resize(tags.size());
    for(int i = 0; i< row.tags.size(); ++i)
    {
        row.tags[i] = tags[i].toStdString();
        cout << "tag" << i << ":" << row.tags[i] << endl;
    }
    row.note = mModel.data(mModel.index(index.row(), ColumnNote)).toString().toUtf8().data();

    cout << "date:" << row.date << endl;
    cout << "io:" << row.io << endl;
    cout << "amout:" << row.amount << endl;
    cout << "note:" << row.note << endl;

    mCashDb.UpdateRow(row.date, row);
}
