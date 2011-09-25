#include "PageChart.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"

PageChart::PageChart()
{
}

PageChart::~PageChart()
{

}

void PageChart::init(const Ui::MainWindow *_ui)
{
    ui = _ui;
}

void PageChart::active()
{
    sqt::switchStackPage(ui->stackedWidgetToolbarExt, 2);
    sqt::switchStackPage(ui->stackedWidgetMoreTool, 2);
    sqt::switchStackPage(ui->stackedWidgetContent, 2);

    ui->stackedWidgetMoreTool->setVisible(true);
}

void PageChart::saveState()
{

}
