#include "PageAccount.h"
#include "TableHolderCash.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"
using namespace sqt;

PageAccount::PageAccount():
    mShouldToolShow(false)
{
}

PageAccount::~PageAccount()
{
}

void PageAccount::init(const Ui::MainWindow *_ui)
{
    ui = _ui;

    mTableCash = new TableHolderCash(ui->tableViewAccount);

    connect(ui->btnAccountInsert, SIGNAL(clicked()), this, SLOT(slotBtnInsertClicked()));
    connect(ui->btnAccountDelete, SIGNAL(clicked()), this, SLOT(slotBtnDeleteClicked()));
    connect(ui->btnAccountQuery, SIGNAL(clicked()), this, SLOT(slotBtnQueryClicked()));
}

void PageAccount::active()
{
    UiHelper::switchStackPage(ui->stackedWidgetToolbarExt, 0);
    UiHelper::switchStackPage(ui->stackedWidgetMoreTool, 0);
    UiHelper::switchStackPage(ui->stackedWidgetContent, 0);

    ui->stackedWidgetMoreTool->setVisible(mShouldToolShow);
}

void PageAccount::saveState()
{

}

void PageAccount::slotBtnInsertClicked()
{
    mTableCash->prepareNewRow();
}

void PageAccount::slotBtnDeleteClicked()
{
    mTableCash->deleteRows();
}

void PageAccount::slotBtnQueryClicked()
{
    mShouldToolShow = ui->stackedWidgetMoreTool->isHidden();

    if (mShouldToolShow) {
        ui->editAccountQuery->setFocus();
    }
    ui->stackedWidgetMoreTool->setShown(mShouldToolShow);
}
