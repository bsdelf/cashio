#include "PageConfig.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"
using namespace sqt;

PageConfig::PageConfig()
{
}

PageConfig::~PageConfig()
{

}

void PageConfig::init(const Ui::MainWindow *_ui)
{
    ui = _ui;
}

void PageConfig::active()
{
    UiHelper::switchStackPage(ui->stackedWidgetToolbarExt, 3);
    UiHelper::switchStackPage(ui->stackedWidgetMoreTool, 3);
    UiHelper::switchStackPage(ui->stackedWidgetContent, 3);

    ui->stackedWidgetMoreTool->setVisible(false);
}


void PageConfig::saveState()
{

}
