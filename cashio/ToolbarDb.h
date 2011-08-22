#ifndef TOOLBARDB_H
#define TOOLBARDB_H

#include <QWidget>

namespace Ui {
    class ToolbarDb;
}

class ToolbarDb : public QWidget
{
    Q_OBJECT

public:
    explicit ToolbarDb(QWidget *parent = 0);
    ~ToolbarDb();

private:
    void setupSlots();

signals:

private slots:
    void slotBtnSearchClicked();

private:
    Ui::ToolbarDb* ui;
};

#endif // TOOLBARDB_H
