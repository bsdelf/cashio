#ifndef TABLERENDERERCASH_H
#define TABLERENDERERCASH_H

#include <QtCore>
#include <QtGui>
#include "CashDb.h"
#include "ComboBoxDelegate.h"

class TableRendererCash : public QObject
{
    Q_OBJECT

public:
    explicit TableRendererCash(QObject *parent = 0);
    ~TableRendererCash();

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

#endif // TABLERENDERERCASH_H
