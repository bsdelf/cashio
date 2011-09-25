#include "PageConfig.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"

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
    sqt::switchStackPage(ui->stackedWidgetToolbarExt, 3);
    sqt::switchStackPage(ui->stackedWidgetMoreTool, 3);
    sqt::switchStackPage(ui->stackedWidgetContent, 3);

    ui->stackedWidgetMoreTool->setVisible(false);
}


void PageConfig::saveState()
{

}
