#include "WidgetGraphBar.h"
#include "ui_WidgetGraphBar.h"

WidgetGraphBar::WidgetGraphBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGraphBar)
{
    ui->setupUi(this);
}

WidgetGraphBar::~WidgetGraphBar()
{
    delete ui;
}
