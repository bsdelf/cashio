#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <sqt/UiHelper.hpp>
#include "ConfDb.h"
using namespace std;

const char CONF_DB_PATH[] = "./conf.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),    
    mConfDb(new ConfDb)
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

    if (QDir().exists(QString::fromAscii(CONF_DB_PATH))) {
        mConfDb->OpenDb(CONF_DB_PATH, false);
    } else {
        mConfDb->OpenDb(CONF_DB_PATH, true);
        QPoint point(rect().center() - QApplication::desktop()->geometry().center());
        mConfDb->SetWindowX(point.x());
        mConfDb->SetWindowY(point.y());
        mConfDb->SetWindowWidth(width());
        mConfDb->SetWindowHeight(height());
        mConfDb->SetLastOpenPath(QDir::homePath().toUtf8().data());
    }
    move(mConfDb->GetWindowX(), mConfDb->GetWindowY());
    resize(mConfDb->GetWindowWidth(), mConfDb->GetWindowHeight());
    mLastOpenPath = QString::fromUtf8(mConfDb->GetLastOpenPath().c_str());
}

MainWindow::~MainWindow()
{
    mConfDb->Begin();
    mConfDb->SetWindowX(window()->x());
    mConfDb->SetWindowY(window()->y());
    mConfDb->SetWindowWidth(rect().width());
    mConfDb->SetWindowHeight(rect().height());
    mConfDb->SetLastOpenPath(mLastOpenPath.toStdString());
    mConfDb->Commit();
    mConfDb->CloseDb();
    delete ui;
}

void MainWindow::setupSlots()
{
    //connect(ui->btnShowDb, SIGNAL(clicked()), this, SLOT(slotBtnShowDbPressed()));
    //connect(ui->btnShowGraph, SIGNAL(clicked()), this, SLOT(slotBtnShowGraphPressed()));

    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(slotBtnOpenClicked()));
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

void MainWindow::slotBtnOpenClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Cashio Database"),
                mLastOpenPath,
                tr("Cashio Database (*.db)"));
    mLastOpenPath = QFileInfo(fileName).absolutePath();
}

void MainWindow::slotBtnAddClicked()
{
    mTableCash.prepareNewRow();
}

void MainWindow::slotBtnDropClicked()
{
    mTableCash.deleteRows();
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
