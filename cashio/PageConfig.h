#ifndef PAGECONFIG_H
#define PAGECONFIG_H

#include <QtGui>
#include "PageInf.h"

class PageConfig: public QObject, public PageInf
{
    Q_OBJECT

public:
    PageConfig();
    virtual ~PageConfig();

    virtual void init(const Ui::MainWindow *_ui);
    virtual void active();
    virtual void saveState();

};

#endif // PAGECONFIG_H
