#include "TableHolderCash.h"
using namespace std;

TableHolderCash::TableHolderCash(QObject *parent) :
    QObject(parent),
    mHasNewRecord(false),
    mHasInvaildCell(false)
{
    openDb("a.db");

    mCombDelegateInOut.addText("In");
    mCombDelegateInOut.addText("Out");
    mCombDelegateInOut.setTextAlignment(Qt::AlignCenter);

    mVaildCellDelegate.setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
    mVaildCellDelegate.setCellColor(QColor(255, 48, 48));
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
    mPtrTable->setAlternatingRowColors(true);

    // setup head
    QStringList  list;
    list << tr("Date") << tr("IO") << tr("Amount") << tr("Tags") << tr("Note");
    mModel.setHorizontalHeaderLabels(list);
    mPtrTable->setItemDelegateForColumn(ColumnDate, &mVaildCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnIO, &mCombDelegateInOut);
    mPtrTable->setItemDelegateForColumn(ColumnAmount, &mVaildCellDelegate);
    //mPtrTable->setItemDelegateForColumn(ColumnTag, &mTagCellDelegate);

    // load table
    DateVector range;
    mCashDb.QueryAllRows(range);
    mCashDb.GetRows(range, mRowPtrVector);
    qDebug() << mRowPtrVector.size() << endl;
    mModel.removeRows(0, mModel.rowCount());
    for (size_t i = 0; i < mRowPtrVector.size(); ++i)
    {
        Row* row = mRowPtrVector[i];
        QList<QStandardItem*> rowList;
        rowList << new QStandardItem(QString::fromStdString(row->date));
        rowList << new QStandardItem(QString::fromUtf8(row->io.c_str()));
        rowList << new QStandardItem(QString::number(row->amount, 'f', 2));
        qDebug() << "row->tags.size():" << row->tags.size() << endl;
        QString tagNames;
        for (size_t i = 0; i < row->tags.size(); ++i)
        {
            tagNames += QString::fromUtf8(row->tags[i].name.c_str()) + " ";
        }
        rowList << new QStandardItem(tagNames); // no tag now
        rowList << new QStandardItem(QString::fromUtf8(row->note.c_str()));
        mModel.appendRow(rowList);
    }
    mPtrTable->setModel(&mModel);

    // adjust head
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    mPtrTable->horizontalHeader()->resizeSections(QHeaderView::Custom);

    connect(&mModel, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(slotModelDataChanged(QStandardItem*)));

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
    mPtrTable->horizontalHeader()->resizeSections(QHeaderView::Custom);

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
    bool cellIsVaild = true;
    QModelIndex index = item->index();
    QString cellValue(mModel.data(index).toString());

    switch (index.column())
    {
    case ColumnDate:
    {
        bool formatVaild = QDateTime::fromString(cellValue, "yyyy-MM-dd HH:mm:ss.zzz").isValid();
        bool keyVaild = !mCashDb.HasRow(cellValue.toStdString());
        cellIsVaild = formatVaild && keyVaild;
    }
        break;

    case ColumnAmount:
        cellValue.toDouble(&cellIsVaild);
        break;
    }
    mHasInvaildCell = !cellIsVaild;

    if (cellIsVaild)
    {
        mVaildCellDelegate.removeIndex(index);

        if (index.column() == ColumnAmount)
        {
            double value = mModel.data(index).toDouble();
            mModel.setData(index, QString::number(value, 'f', 2));
        }

        if (mHasNewRecord)
            syncNewRecord();
        else
            updateRecord(index);
    }
    else
    {
        mVaildCellDelegate.insertIndex(index);
    }
    // resize
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    qDebug() << "r:" << item->row() << " c:" << item->column() << endl;
}

bool TableHolderCash::hasInvaildCell()
{
    if (!mHasInvaildCell)
        return false;

    QMessageBox msgBox(mPtrTable);
    msgBox.setWindowTitle(tr("Error"));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Please correct the invaild cell first!"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    return true;
}

void TableHolderCash::syncNewRecord()
{
    if (!mHasNewRecord)
        return;
    qDebug() << "sync" << endl;

    Row* row = new Row;
    row->date = mModel.data(mModel.index(0, ColumnDate)).toString().toStdString();
    row->io = mModel.data(mModel.index(0, ColumnIO)).toString().toStdString();
    row->amount = mModel.data(mModel.index(0, ColumnAmount)).toDouble();
    QStringList tags = mModel.data(mModel.index(0, ColumnTag)).toString().split(QRegExp("\\s+"), QString::SkipEmptyParts);
    row->tags.resize(tags.size());
    for(size_t i = 0; i< row->tags.size(); ++i)
    {
        row->tags[i].name = tags[i].toUtf8().data();
        row->tags[i].color = Qt::red;
        qDebug() << "tag" << i << ":" << row->tags[i].name.c_str() << endl;
    }
    row->note = mModel.data(mModel.index(0, ColumnNote)).toString().toStdString();

    qDebug() << "date:" << row->date.c_str() << endl;
    qDebug() << "io:" << QString::fromUtf8(row->io.c_str()) << endl;
    qDebug() << "amout:" << row->amount << endl;
    qDebug() << "note:" << QString::fromUtf8(row->note.c_str()) << endl;

    mRowPtrVector.insert(mRowPtrVector.begin(), row);
    mCashDb.InsertRow(row);
    mHasNewRecord = false;
}

void TableHolderCash::updateRecord(const QModelIndex &index)
{
    qDebug() << "update" << endl;

    Row newRow;
    newRow.date = mModel.data(mModel.index(index.row(), ColumnDate)).toString().toStdString();
    newRow.io = mModel.data(mModel.index(index.row(), ColumnIO)).toString().toUtf8().data();
    newRow.amount = mModel.data(mModel.index(index.row(), ColumnAmount)).toDouble();
    QStringList tagNames = mModel.data(mModel.index(index.row(), ColumnTag)).toString().split(QRegExp("\\s+"), QString::SkipEmptyParts);
    newRow.tags.resize(tagNames.size());
    for(size_t i = 0; i< newRow.tags.size(); ++i)
    {
        newRow.tags[i].name = tagNames[i].toUtf8().data();
        newRow.tags[i].color = Qt::red;
        qDebug() << "tag" << i << ":" << newRow.tags[i].name.c_str() << endl;
    }
    newRow.note = mModel.data(mModel.index(index.row(), ColumnNote)).toString().toUtf8().data();

    Row& oldRow = *mRowPtrVector[index.row()];

    qDebug() << "old date:" << oldRow.date.c_str() << endl;
    qDebug() << "new date:" << newRow.date.c_str() << endl;
    qDebug() << "io:" << QString::fromUtf8(newRow.io.c_str()) << endl;
    qDebug() << "amout:" << newRow.amount << endl;
    qDebug() << "tag count:" << tagNames.size();
    qDebug() << "note:" << QString::fromUtf8(newRow.note.c_str()) << endl;


    mCashDb.UpdateRow(oldRow.date, newRow);
    oldRow.tags.clear();
    oldRow = newRow;
}
