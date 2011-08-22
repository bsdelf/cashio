#ifndef WidgetDbBar_H
#define WidgetDbBar_H

#include <QWidget>

namespace Ui {
    class WidgetDbBar;
}

class WidgetDbBar : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDbBar(QWidget *parent = 0);
    ~WidgetDbBar();

private:
    void setupSignals();

private:
    Ui::WidgetDbBar* ui;

signals:
    void sigBtnSearchClicked();

};

#endif // WidgetDbBar_H
