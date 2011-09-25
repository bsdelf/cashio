#include "TableHolderCash.h"
#include <ctime>

TableHolderCash::TableHolderCash(QTableView* table) :
    mHasNewRecord(false),
    mHasInvaildCell(false)
{
    openDb("a.db");   

    mDateCellDelegate.setTextAlignment(Qt::AlignCenter);

    mIOCellDelegate.addText(tr("In"));
    mIOCellDelegate.addText(tr("Out"));
    mIOCellDelegate.setTextAlignment(Qt::AlignCenter);

    mAmountCellDelegate.setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);

    mNoteCellDelegate.setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    setupTable(table);
}

TableHolderCash::~TableHolderCash()
{

}

void TableHolderCash::openDb(const QString &path)
{
    mCashDb.OpenDb(path.toUtf8().data());
    mCashDb.InitDb();
}

void TableHolderCash::closeDb()
{
    mCashDb.CloseDb();
}

void TableHolderCash::setupTable(QTableView *table)
{
    mPtrTable = table;   

    // setup head
    QStringList list;
    list << tr("Date") << tr("IO") << tr("Amount") << tr("Tags") << tr("Note");
    mModel.setHorizontalHeaderLabels(list);
    mPtrTable->setItemDelegateForColumn(ColumnDate, &mDateCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnIO, &mIOCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnAmount, &mAmountCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnTag, &mTagCellDelegate);
    mPtrTable->setItemDelegateForColumn(ColumnNote, &mNoteCellDelegate);

    // setup TagCellDelegate
    TagVector tags;
    mCashDb.GetTags(tags);
    mTagCellDelegate.setTagFont(mPtrTable->font());
    mTagCellDelegate.setTagSpace(10);
    mTagCellDelegate.reserveTagColor(tags.size());
    for (size_t i = 0; i < tags.size(); ++i) {
        mTagCellDelegate.insertTagColorPair(
          QString::fromUtf8(tags[i].name.c_str()), tags[i].color);
    }

    mPtrTable->setModel(&mModel);

    // load table
    RowPtrVector rowPtrs;
    mCashDb.QueryAllRows(mUuidRange);
    mCashDb.GetRows(mUuidRange, rowPtrs);

    mModel.removeRows(0, mModel.rowCount());
    mTagCellDelegate.clearRowTagPtrs();
    mTagCellDelegate.reserveRowTagPtrs(rowPtrs.size());
    for (size_t i = 0; i < rowPtrs.size(); ++i) {
        Row* row = rowPtrs[i];
        QList<QStandardItem*> rowList;
        rowList << new QStandardItem(QString::fromStdString(row->date));
        rowList << new QStandardItem(QString::fromUtf8(row->io.c_str()));
        rowList << new QStandardItem(QString::number(row->amount, 'f', 2));
        QString tagNames;
        QStringList tagNameList;
        for (size_t i = 0; i < row->tags.size(); ++i) {
            QString tagName = QString::fromUtf8(row->tags[i].name.c_str());
            tagNames += tagName + " ";
            tagNameList << tagName;
        }
        rowList << new QStandardItem(tagNames);
        rowList << new QStandardItem(QString::fromUtf8(row->note.c_str()));
        mModel.appendRow(rowList);
        mTagCellDelegate.appendRowTag(tagNameList);
        delete row;
    }    

    // adjust head
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    mPtrTable->horizontalHeader()->resizeSections(QHeaderView::Custom);

    connect(&mModel, SIGNAL(itemChanged(QStandardItem*)),
            this, SLOT(slotModelDataChanged(QStandardItem*)));

}

void TableHolderCash::prepareNewRow()
{
    if (mHasInvaildCell) {
        notifyInvaildCell();
        return;
    }

    QList<QStandardItem*> row;
    row << new QStandardItem(QString::fromStdString(mCashDb.GetTime()));
    row << new QStandardItem(tr("Out"));
    row << new QStandardItem();
    row << new QStandardItem();

    // if we already have one,
    // clear it and insert new one.
    if (mHasNewRecord) {
        mModel.removeRow(0);
        mTagCellDelegate.removeRowTag(0);
    }
    mModel.insertRow(0, row);
    mTagCellDelegate.insertRowTag(0, QStringList());
    mHasNewRecord = true;

    // adjust view
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    mPtrTable->horizontalHeader()->resizeSections(QHeaderView::Custom);

    // begin to edit
    QModelIndex index(mModel.index(0, ColumnAmount));
    mPtrTable->setCurrentIndex(index);
    mPtrTable->edit(index);
}

void TableHolderCash::deleteRows()
{
    // pick all #strictly# selected rows
    QItemSelectionModel* selectionModel = mPtrTable->selectionModel();
    QModelIndexList indexList(selectionModel->selectedRows());
    int selectionCount = selectionModel->selectedRows().size();

    if (selectionCount <= 0)
        return;

    if (!mHasInvaildCell) {
        if (!confirmDeleteRows(indexList))
            return;
        for (int i = 0; i < selectionCount; ++i) {
            QItemSelectionModel* selectionModel = mPtrTable->selectionModel();
            QModelIndexList indexList(selectionModel->selectedRows());
            const int row = indexList.front().row();
            mModel.removeRow(row);
            mCashDb.DeleteRow(mUuidRange[row]);
            mTagCellDelegate.removeRowTag(row);
            mUuidRange.erase(mUuidRange.begin()+row);
        }
    } else {
        if (mHasNewRecord && selectionCount == 1) {
            mModel.removeRow(0);
            mTagCellDelegate.removeRowTag(0);
            if (mHasInvaildCell) {
                mDateCellDelegate.removeHighlightIndex(mModel.index(0, ColumnDate));
                mAmountCellDelegate.removeHighlightIndex(mModel.index(0, ColumnAmount));
                mHasInvaildCell = false;
            }
            mHasNewRecord = false;
        } else if (selectionCount != 0) {
            notifyInvaildCell();
        }
    }
}

void TableHolderCash::slotModelDataChanged(QStandardItem * item)
{
    // check whether the cell is vaild
    bool cellIsVaild = true;
    QModelIndex index(item->index());
    QString cellValue(mModel.data(index).toString());

    switch (index.column()) {
    case ColumnDate:
    {
        cellIsVaild = QDateTime::fromString(cellValue, "yyyy-MM-dd HH:mm:ss").isValid();
    }
        break;

    case ColumnAmount:
        cellValue.toDouble(&cellIsVaild);
        break;
    }
    mHasInvaildCell = !cellIsVaild;

    if (cellIsVaild) {
        mDateCellDelegate.removeHighlightIndex(index);
        mAmountCellDelegate.removeHighlightIndex(index);

        if (index.column() == ColumnAmount) {
            double value = mModel.data(index).toDouble();
            mModel.setData(index, QString::number(value, 'f', 2));
        }

        if (mHasNewRecord)
            syncNewRecord();
        else
            updateRecord(index);
    } else {
        mDateCellDelegate.insertHighlightIndex(index, QColor(255, 48, 48));
        mAmountCellDelegate.insertHighlightIndex(index, QColor(255, 48, 48));
    }
    // resize
    mPtrTable->resizeColumnsToContents();
    mPtrTable->horizontalHeader()->setStretchLastSection(true);
    qDebug() << "row:" << item->row() << " column:" << item->column();
}

void TableHolderCash::notifyInvaildCell()
{
    QMessageBox msgBox(mPtrTable);
    msgBox.setWindowTitle(tr("Error"));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Please correct the invaild cell first!"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

bool TableHolderCash::confirmDeleteRows(const QModelIndexList& list)
{
    QString text(tr("The following rows will be deleted:"));
    text += "\n" + QString::number(list[0].row()+1);
    for (int i = 1; i < list.size(); ++i) {
        text += ", ";
        if (i%10 == 0)
            text += '\n';
        text += QString::number(list[i].row()+1);
    }

    QMessageBox msgBox(mPtrTable);
    msgBox.setWindowTitle(tr("Info"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    return (msgBox.exec() == QMessageBox::Ok) ? true : false;
}

void TableHolderCash::syncNewRecord()
{
    if (!mHasNewRecord)
        return;
    qDebug() << "sync!!";

    Row* row = new Row;
    row->date = mModel.index(0, ColumnDate).data().toString().toStdString();
    row->io = mModel.index(0, ColumnIO).data().toString().toStdString();
    row->amount = mModel.index(0, ColumnAmount).data().toDouble();
    QStringList tagList = mModel.index(0, ColumnTag).data().toString().split(QRegExp("\\s+"), QString::SkipEmptyParts);
    row->tags.resize(tagList.size());
    for(size_t i = 0; i< row->tags.size(); ++i) {
        row->tags[i].name = "";
        row->tags[i].color = 0;
        qDebug() << "tag" << i << ":" << row->tags[i].name.c_str();
    }
    row->note = mModel.index(0, ColumnNote).data().toString().toStdString();

    qDebug() << "date:" << row->date.c_str();
    qDebug() << "io:" << QString::fromUtf8(row->io.c_str());
    qDebug() << "amout:" << row->amount;
    qDebug() << "note:" << QString::fromUtf8(row->note.c_str());

    string uuid(QUuid::createUuid().toString().toStdString());
    mUuidRange.insert(mUuidRange.begin(), uuid);
    mTagCellDelegate.updateRowTag(0, tagList);
    mCashDb.InsertRow(uuid, row);

    mHasNewRecord = false;
}

void TableHolderCash::updateRecord(const QModelIndex &index)
{
    qDebug() << "update!!";

    const int row = index.row();

    // pick new row data in table view
    Row newRow;
    newRow.date = mModel.index(row, ColumnDate).data().toString().toStdString();
    newRow.io = mModel.index(row, ColumnIO).data().toString().toUtf8().data();
    newRow.amount = mModel.index(row, ColumnAmount).data().toDouble();
    newRow.note = mModel.index(row, ColumnNote).data().toString().toUtf8().data();

    // special handle for tags
    QStringList tagNames(mModel.index(row, ColumnTag).data().toString().split(QRegExp("\\s+"), QString::SkipEmptyParts));
    newRow.tags.resize(tagNames.size());
    UuidVector tagUuids;
    tagUuids.resize(tagNames.size());
    // NOTE: Under Windows the rand() is not as random as Unix,
    // so we split color into r/g/b, instead of an single random integer[0, 2^31).
    srand(time(NULL));
    for (size_t i = 0; i< newRow.tags.size(); ++i) {
        newRow.tags[i].name = tagNames[i].toUtf8().data();
        newRow.tags[i].color = (rand()%256)<<16 | (rand()%256)<<8 | (rand()%256);
        tagUuids[i] = QUuid::createUuid().toString().toStdString();
        qDebug() << "tag" << i << ":" << newRow.tags[i].name.c_str();
        qDebug() << "color:" << newRow.tags[i].color;
    }

    // write to database together with out "cache"
    qDebug() << "date:" << newRow.date.c_str();
    qDebug() << "io:" << QString::fromUtf8(newRow.io.c_str());
    qDebug() << "amout:" << newRow.amount;
    qDebug() << "tag count:" << tagNames.size();
    qDebug() << "note:" << QString::fromUtf8(newRow.note.c_str());

    string uuid(mUuidRange[row]);
    TagVector newTags;
    mCashDb.UpdateRow(uuid, newRow, tagUuids, newTags);
    mTagCellDelegate.updateRowTag(row, tagNames);
    for (size_t i = 0; i < newTags.size(); ++i) {
        mTagCellDelegate.insertTagColorPair(
          QString::fromUtf8(newTags[i].name.c_str()), newTags[i].color);
    }
}
