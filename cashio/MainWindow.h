#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "WidgetDbBar.h"
#include "WidgetGraphBar.h"
#include "TableRendererCash.h"

namespace Ui {
    class MainWindow;
}

enum PageIndex {
    PageDatabase = 0,
    PageGraphics,
};

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupSlots();
    void switchPage(PageIndex pageName);

public slots:
    void slotDbBarBtnInsertClicked();
    void slotDbBarBtnDropClicked();
    void slotDbBarBtnSearchClicked();
    void slotDbBarBtnSaveClicked();

private slots:
    void slotCbxPageIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QStackedLayout* mBarLayout;
    WidgetDbBar mDbBar;
    WidgetGraphBar mGraphBar;
    TableRendererCash mRendererCash;
};

#endif // MAINWINDOW_H
