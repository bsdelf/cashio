#ifndef TableHolderCash_H
#define TableHolderCash_H

#include <QtCore>
#include <QtGui>
#include "CashDb.h"
#include "QComboBoxDelegate.hpp"
#include "QBaseCellDelegate.hpp"
#include "QTagCellDelegate.hpp"

enum ColumnIndex
{
    ColumnDate = 0,
    ColumnIO,
    ColumnAmount,
    ColumnTag,
    ColumnNote
};

class TableHolderCash : public QObject
{
    Q_OBJECT

public:
    explicit TableHolderCash(QTableView* table);
    ~TableHolderCash();

public:
    void openDb(const QString& path);
    void closeDb();

public:
    void prepareNewRow();
    void deleteRows();

private:
    void setupTable(QTableView* table);
    void notifyInvaildCell();
    bool confirmDeleteRows(const QModelIndexList& list);
    void syncNewRecord();
    void updateRecord(const QModelIndex& index);

signals:

private slots:
    void slotModelDataChanged(QStandardItem * item);

private:
    QTableView* mPtrTable;
    QStandardItemModel mModel;
    CashDb mCashDb;

    sqt::QBaseCellDelegate mDateCellDelegate;
    sqt::QComboBoxDelegate mIOCellDelegate;
    sqt::QBaseCellDelegate mAmountCellDelegate;
    sqt::QTagCellDelegate mTagCellDelegate;
    sqt::QBaseCellDelegate mNoteCellDelegate;

    bool mHasNewRecord;
    bool mHasInvaildCell;

    UuidVector mUuidRange;
};

#endif // TableHolderCash_H
