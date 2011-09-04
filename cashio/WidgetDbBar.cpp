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
    connect(ui->btnInsert, SIGNAL(clicked()), this, SIGNAL(sigBtnInsertClicked()));
    connect(ui->btnDrop, SIGNAL(clicked()), this, SIGNAL(sigBtnDropClicked()));
    connect(ui->btnSearch, SIGNAL(clicked()), this, SIGNAL(sigBtnSearchClicked()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SIGNAL(sigBtnSaveClicked()));
}
    //bool isHidden = ui->widgetSearch->isHidden();
    //ui->widgetSearch->setShown(isHidden);
