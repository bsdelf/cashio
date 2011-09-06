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
    ui->widgetToolExt->setCurrentIndex(ToolExtQuery);
    mRendererCash.setupTable(ui->tableView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSlots()
{
    connect(ui->btnShowDb, SIGNAL(clicked()), this, SLOT(slotBtnShowDbPressed()));
    connect(ui->btnShowGraph, SIGNAL(clicked()), this, SLOT(slotBtnShowGraphPressed()));

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(slotBtnAddClicked()));
    connect(ui->btnDrop, SIGNAL(clicked()), this, SLOT(slotBtnDropClicked()));
    connect(ui->btnQuery, SIGNAL(clicked()), this, SLOT(slotBtnQueryClicked()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(slotBtnSaveClicked()));

    //connect(ui->cbxPage, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbxPageIndexChanged(int)));

    connect(ui->btnEnterSqlMode, SIGNAL(clicked()), this, SLOT(slotBtnEnterSqlModeClicked()));
    connect(ui->btnQuitSqlMode, SIGNAL(clicked()), this, SLOT(slotBtnQuitSqlModeClicked()));
}

void MainWindow::switchContent(ContentIndex index)
{
    switch (index)
    {
    case ContentDb:
    {
        ui->btnShowDb->setChecked(true);
        ui->btnShowGraph->setChecked(false);
    }
        break;

    case ContentGraph:
    {
        ui->btnShowDb->setChecked(false);
        ui->btnShowGraph->setChecked(true);
    }
        break;
    }
}

void MainWindow::switchToolBar(ToolBarIndex pageIndex)
{
    ui->widgetToolBar->setCurrentIndex(pageIndex);
    if (pageIndex != ToolBarDatabase)
    {
        ui->widgetToolExt->setShown(false);
    }
}

void MainWindow::slotBtnShowDbPressed()
{
    if (ui->btnShowDb->isChecked())
        ui->btnShowDb->setChecked(true);
    ui->btnShowGraph->setChecked(false);
}

void MainWindow::slotBtnShowGraphPressed()
{
    ui->btnShowDb->setChecked(false);
}

void MainWindow::slotBtnAddClicked()
{
    mRendererCash.prepareNewRow();
}

void MainWindow::slotBtnDropClicked()
{

}

void MainWindow::slotBtnQueryClicked()
{
    bool shouldShow = ui->widgetToolExt->isHidden();

    if (shouldShow)
    {
        //mToolExtLayout->setCurrentIndex(ToolExtQuery);
        //ui->editQuery->setFocus();
    }
    ui->widgetToolExt->setShown(shouldShow);
}

void MainWindow::slotBtnSaveClicked()
{
    mRendererCash.tryToSaveRows();
}

void MainWindow::slotCbxPageIndexChanged(int index)
{
    ToolBarIndex toolbarIndex = (ToolBarIndex)index;
    switchToolBar(toolbarIndex);
}

void MainWindow::slotBtnEnterSqlModeClicked()
{
    sqt::switchStackPage(ui->widgetToolExt, ToolExtQuerySql);
}

void MainWindow::slotBtnQuitSqlModeClicked()
{
    sqt::switchStackPage(ui->widgetToolExt, ToolExtQuery);
}
