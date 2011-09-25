#ifndef PAGEGRAPH_H
#define PAGEGRAPH_H

#include <QtGui>
#include "PageInf.h"

class PageGraph: public QObject, public PageInf
{
    Q_OBJECT

public:
    PageGraph();
    virtual ~PageGraph();

    virtual void init(const Ui::MainWindow *_ui);
    virtual void active();
    virtual void saveState();
};

#endif // PAGEGRAPH_H
