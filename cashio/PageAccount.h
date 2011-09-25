#ifndef PAGEACCOUNT_H
#define PAGEACCOUNT_H

#include <QtGui>
#include "PageInf.h"

class TableHolderCash;

class PageAccount: public QObject, public PageInf
{
    Q_OBJECT

public:
    PageAccount();
    virtual ~PageAccount();

    virtual void init(const Ui::MainWindow *_ui);
    virtual void active();
    virtual void saveState();

private slots:
    void slotBtnInsertClicked();
    void slotBtnDeleteClicked();
    void slotBtnQueryClicked();

private:
    const Ui::MainWindow* ui;
    TableHolderCash* mTableCash;

    bool mShouldToolShow;
};

#endif // PAGEACCOUNT_H
