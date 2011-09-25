#ifndef PAGETAG_H
#define PAGETAG_H

#include <QtGui>
#include "PageInf.h"

class PageTag: public QObject, public PageInf
{
    Q_OBJECT

public:
    PageTag();
    virtual ~PageTag();

    virtual void init(const Ui::MainWindow *_ui);
    virtual void active();
    virtual void saveState();

private slots:
    void slotBtnInsertClicked();
    void slotBtnDeleteClicked();
    void slotBtnQueryClicked();
    void slotBtnClearClicked();

private:
    const Ui::MainWindow* ui;
    bool mShouldToolShow;
};

#endif // PAGETAG_H
