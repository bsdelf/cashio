#include "WidgetDbBar.h"
#include "ui_WidgetDbBar.h"

WidgetDbBar::WidgetDbBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDbBar)
{
    ui->setupUi(this);
    setupSignals();
}

WidgetDbBar::~WidgetDbBar()
{

}

void WidgetDbBar::setupSignals()
{
    connect(ui->btnSearch, SIGNAL(clicked()), this, SIGNAL(sigBtnSearchClicked()));
}
    //bool isHidden = ui->widgetSearch->isHidden();
    //ui->widgetSearch->setShown(isHidden);
