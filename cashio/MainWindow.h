#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "TableHolderCash.h"

namespace Ui {
    class MainWindow;
}

enum ContentIndex {
    ContentDb = 0,
    ContentGraph,
};

enum ToolBarIndex {
    ToolBarDatabase = 0,
    ToolBarGraphics,
};

enum ToolExtIndex {
    ToolExtQueryCond = 0,
    ToolExtQuerySql,
};

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupSlots();
    void switchContent(ContentIndex index);
    void switchToolBar(ToolBarIndex index);
    void focusCurrentEditQuery();

private slots:
    void slotBtnShowDbPressed();
    void slotBtnShowGraphPressed();

    void slotBtnAddClicked();
    void slotBtnDropClicked();
    void slotBtnQueryClicked();

    void slotBtnEnterSqlModeClicked();
    void slotBtnQuitSqlModeClicked();
    void slotCbxPageIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    TableHolderCash mTableCash;
};

#endif // MAINWINDOW_H
