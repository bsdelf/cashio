#include "ToolbarDb.h"
#include "ui_ToolbarDb.h"

ToolbarDb::ToolbarDb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolbarDb)
{
    ui->setupUi(this);
    setupSlots();

    ui->widgetSearch->hide();
}

ToolbarDb::~ToolbarDb()
{

}

void ToolbarDb::setupSlots()
{
    connect(ui->btnSearch, SIGNAL(clicked()), this, SLOT(slotBtnSearchClicked()));
}

void ToolbarDb::slotBtnSearchClicked()
{
    bool isHidden = ui->widgetSearch->isHidden();
    ui->widgetSearch->setShown(isHidden);
}
