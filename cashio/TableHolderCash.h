#ifndef TableHolderCash_H
#define TableHolderCash_H

#include <QtCore>
#include <QtGui>
#include "CashDb.h"
#include "ComboBoxDelegate.h"

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

signals:

private slots:
    void slotModelDataChanged(QStandardItem * item);

private:
    QTableView* mPtrTable;
    QStandardItemModel mModel;
    CashDb mCashDb;
    ComboBoxDelegate mCombDelegateInOut;
    bool mHasNewRow;
};

#endif // TableHolderCash_H
