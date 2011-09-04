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

    mCashDb.OpenDb("a.db");
    mCashDb.InitDb();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSlots()
{
    connect(&mDbBar, SIGNAL(sigBtnInsertClicked()), this, SLOT(slotDbBarBtnInsertClicked()));
    connect(&mDbBar, SIGNAL(sigBtnDropClicked()), this, SLOT(slotDbBarBtnDropClicked()));
    connect(&mDbBar, SIGNAL(sigBtnSearchClicked()), this, SLOT(slotDbBarBtnSearchClicked()));
    connect(&mDbBar, SIGNAL(sigBtnSaveClicked()), this, SLOT(slotDbBarBtnSaveClicked()));

    connect(ui->cbxPage, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbxPageIndexChanged(int)));
}

void MainWindow::switchPage(PageIndex pageIndex)
{
    mBarLayout->setCurrentIndex(pageIndex);
    if (pageIndex != PageDatabase)
        ui->widgetSearchBar->setShown(false);
}

void MainWindow::slotDbBarBtnInsertClicked()
{

}

void MainWindow::slotDbBarBtnDropClicked()
{

}

void MainWindow::slotDbBarBtnSearchClicked()
{
    bool shouldShow = ui->widgetSearchBar->isHidden();
    ui->widgetSearchBar->setShown(shouldShow);
    if (shouldShow)
        ui->editSearch->setFocus();
}

void MainWindow::slotDbBarBtnSaveClicked()
{

}

void MainWindow::slotCbxPageIndexChanged(int index)
{
    PageIndex pageIndex = (PageIndex)index;
    switchPage(pageIndex);
}
