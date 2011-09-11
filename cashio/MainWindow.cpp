#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <sqt/UiHelper.hpp>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSlots();   

    slotBtnShowDbPressed();
    ui->widgetToolExt->hide();
    sqt::switchStackPage(ui->widgetToolExt, ToolExtQueryCond);
    mTableCash.setupTable(ui->tableView);

    QMenu* menu = new QMenu;
    menu->addAction("a");
    menu->addAction("b");
    ui->btnQueryCond->setMenu(menu);

    QCompleter* c = new QCompleter();
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    c->setCompletionColumn(0);
    QStringList keyWords;
    keyWords << "date" << "io" << "amount" << "tags" << "note";
    c->setModel(new QStringListModel(keyWords));
    ui->editQueryCond->setCompleter(c);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSlots()
{
    //connect(ui->btnShowDb, SIGNAL(clicked()), this, SLOT(slotBtnShowDbPressed()));
    //connect(ui->btnShowGraph, SIGNAL(clicked()), this, SLOT(slotBtnShowGraphPressed()));

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(slotBtnAddClicked()));
    connect(ui->btnDrop, SIGNAL(clicked()), this, SLOT(slotBtnDropClicked()));
    connect(ui->btnQuery, SIGNAL(clicked()), this, SLOT(slotBtnQueryClicked()));

    connect(ui->btnEnterSqlMode, SIGNAL(clicked()), this, SLOT(slotBtnEnterSqlModeClicked()));
    connect(ui->btnQuitSqlMode, SIGNAL(clicked()), this, SLOT(slotBtnQuitSqlModeClicked()));
}

void MainWindow::switchContent(ContentIndex index)
{

}

void MainWindow::switchToolBar(ToolBarIndex pageIndex)
{
    ui->widgetToolBar->setCurrentIndex(pageIndex);
    if (pageIndex != ToolBarDatabase)
    {
        ui->widgetToolExt->setShown(false);
    }
}

void MainWindow::focusCurrentEditQuery()
{
    switch (ui->widgetToolExt->currentIndex()) {
    case ToolExtQueryCond:
        ui->editQueryCond->setFocus();
        break;

    case ToolExtQuerySql:
        ui->editQuerySql->setFocus();
        break;
    }
}

void MainWindow::slotBtnShowDbPressed()
{
}

void MainWindow::slotBtnShowGraphPressed()
{

}

void MainWindow::slotBtnAddClicked()
{
    mTableCash.prepareNewRow();
}

void MainWindow::slotBtnDropClicked()
{
    mTableCash.removeRows();
}

void MainWindow::slotBtnQueryClicked()
{
    bool shouldShow = ui->widgetToolExt->isHidden();

    if (shouldShow) {
        focusCurrentEditQuery();
    }
    ui->widgetToolExt->setShown(shouldShow);
}

void MainWindow::slotCbxPageIndexChanged(int index)
{
    ToolBarIndex toolbarIndex = (ToolBarIndex)index;
    switchToolBar(toolbarIndex);
}

void MainWindow::slotBtnEnterSqlModeClicked()
{
    sqt::switchStackPage(ui->widgetToolExt, ToolExtQuerySql);
    focusCurrentEditQuery();
}

void MainWindow::slotBtnQuitSqlModeClicked()
{
    sqt::switchStackPage(ui->widgetToolExt, ToolExtQueryCond);
    focusCurrentEditQuery();
}
