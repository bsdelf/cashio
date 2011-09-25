#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "PageAccount.h"
#include "ConfDb.h"

class ConfDb;

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

    void loadConf();
    void saveConf();

private:
    void setupSlots();

private slots:
    void slotBtnOpenClicked();
    void slotBtnCreateClicked();

    void slotBtnAccountClicked();    

    void slotBtnTagClicked();
    void slotBtnTagInsertClicked();
    void slotBtnTagDeleteClicked();
    void slotBtnTagQueryClicked();
    void slotBtnTagClearClicked();

    void slotBtnGraphClicked();
    void slotBtnConfigClicked();

private:
    Ui::MainWindow *ui;

    QString mLastOpenPath;

    ConfDb* mConfDb;

    PageAccount mPageAccount;
};

#endif // MAINWINDOW_H
