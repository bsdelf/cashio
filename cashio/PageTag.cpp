#include "PageTag.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"

PageTag::PageTag():
    mShouldToolShow(false)
{
}

PageTag::~PageTag()
{

}

void PageTag::init(const Ui::MainWindow *_ui)
{
    ui = _ui;

    connect(ui->btnTagInsert, SIGNAL(clicked()), this, SLOT(slotBtnInsertClicked()));
    connect(ui->btnTagDelete, SIGNAL(clicked()), this, SLOT(slotBtnDeleteClicked()));
    connect(ui->btnTagQuery, SIGNAL(clicked()), this, SLOT(slotBtnQueryClicked()));
    connect(ui->btnTagClear, SIGNAL(clicked()), this, SLOT(slotBtnClearClicked()));
}

void PageTag::active()
{
    sqt::switchStackPage(ui->stackedWidgetToolbarExt, 1);
    sqt::switchStackPage(ui->stackedWidgetTool, 1);
    sqt::switchStackPage(ui->stackedWidgetContent, 1);

    ui->stackedWidgetTool->setVisible(mShouldToolShow);
}

void PageTag::saveState()
{

}

void PageTag::slotBtnInsertClicked()
{

}

void PageTag::slotBtnDeleteClicked()
{

}

void PageTag::slotBtnQueryClicked()
{
    mShouldToolShow = ui->stackedWidgetTool->isHidden();

    if (mShouldToolShow) {
        ui->editAccountQuery->setFocus();
    }
    ui->stackedWidgetTool->setShown(mShouldToolShow);
}

void PageTag::slotBtnClearClicked()
{

}
