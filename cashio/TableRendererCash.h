#ifndef TABLERENDERERCASH_H
#define TABLERENDERERCASH_H

#include <QtCore>
#include <QtGui>
#include "CashDb.h"

class TableRendererCash : public QObject
{
    Q_OBJECT
public:
    explicit TableRendererCash(QObject *parent = 0);

public:
    void setupTable(QTableView* view);
    void renderTable();

signals:

public slots:

private:
    QTableView* mPtrTable;
    QStandardItemModel mModel;
    CashDb mCashDb;
};

#endif // TABLERENDERERCASH_H
