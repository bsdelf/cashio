#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "PageAccount.h"
#include "PageTag.h"
#include "PageChart.h"
#include "PageConfig.h"

#include "ConfDb.h"

class ConfDb;

namespace Ui {
    class MainWindow;
}

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
    void slotBtnChartClicked();
    void slotBtnConfigClicked();

private:
    Ui::MainWindow *ui;

    QString mLastOpenPath;

    ConfDb* mConfDb;

    PageAccount mPageAccount;
    PageTag mPageTag;
    PageChart mPageChart;
    PageConfig mPageConfig;

};

#endif // MAINWINDOW_H
