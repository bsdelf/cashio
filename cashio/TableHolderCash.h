#ifndef TableHolderCash_H
#define TableHolderCash_H

#include <QtCore>
#include <QtGui>
#include "CashDb.h"
#include "QComboBoxDelegate.hpp"
#include "QColorfulCellDelegate.hpp"

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
    explicit TableHolderCash(QObject *parent = 0);
    ~TableHolderCash();

public:
    void openDb(const QString& path);
    void closeDb();

    void setupTable(QTableView* table);
    void unsetupTable();

public:
    void prepareNewRow();
    bool tryToSaveRows();
    bool rmSelectedRows();

private:
    bool hasInvaildCell();
    void syncNewRecord();

signals:

private slots:
    void slotModelDataChanged(QStandardItem * item);

private:
    QTableView* mPtrTable;
    QStandardItemModel mModel;
    CashDb mCashDb;

    sqt::QComboBoxDelegate mCombDelegateInOut;
    sqt::QColorfulCellDelegate mColorfulCellDelegate;

    bool mHasNewRecord;
    bool mHasInvaildCell;

    TagVector mTagVector;
    RowVector mRowVector;
};

#endif // TableHolderCash_H
