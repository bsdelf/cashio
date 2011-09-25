#ifndef PAGECHART_H
#define PAGECHART_H

#include <QtGui>
#include "PageInf.h"

class PageChart: public QObject, public PageInf
{
    Q_OBJECT

public:
    PageChart();
    virtual ~PageChart();

    virtual void init(const Ui::MainWindow *_ui);
    virtual void active();
    virtual void saveState();

private slots:
    void drawSomeThing();

private:
    const Ui::MainWindow* ui;
};

#endif // PAGECHART_H
