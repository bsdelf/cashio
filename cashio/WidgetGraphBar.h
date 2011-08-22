#ifndef WidgetGraphBar_H
#define WidgetGraphBar_H

#include <QWidget>

namespace Ui {
    class WidgetGraphBar;
}

class WidgetGraphBar : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetGraphBar(QWidget *parent = 0);
    ~WidgetGraphBar();

private:
    Ui::WidgetGraphBar *ui;
};

#endif // WidgetGraphBar_H
