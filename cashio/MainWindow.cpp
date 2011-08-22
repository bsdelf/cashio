#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSlots();

    mBarLayout = new QStackedLayout(ui->widgetBar);
    mBarLayout->addWidget(&mDbBar);
    mBarLayout->addWidget(&mGraphBar);
    ui->widgetBar->setLayout(mBarLayout);

    switchPage(PageDatabase);
    ui->widgetSearchBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSlots()
{
    connect(&mDbBar, SIGNAL(sigBtnSearchClicked()), this, SLOT(slotDbBarBtnSearchClicked()));
    connect(ui->cbxPage, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbxPageIndexChanged(int)));
}

void MainWindow::switchPage(PageIndex pageIndex)
{
    mBarLayout->setCurrentIndex(pageIndex);
    if (pageIndex != PageDatabase)
        ui->widgetSearchBar->setShown(false);
}

void MainWindow::slotDbBarBtnSearchClicked()
{
    bool shouldShow = ui->widgetSearchBar->isHidden();
    ui->widgetSearchBar->setShown(shouldShow);
    if (shouldShow)
        ui->editSearch->setFocus();
}

void MainWindow::slotCbxPageIndexChanged(int index)
{
    PageIndex pageIndex = (PageIndex)index;
    switchPage(pageIndex);
}
