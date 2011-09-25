#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <sqt/UiHelper.hpp>
#include "ConfDb.h"
using namespace std;

const char CONF_DB_PATH[] = "./conf.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),    
    mConfDb(new ConfDb)
{
    ui->setupUi(this);

    mPageAccount.init(ui);
    mPageTag.init(ui);
    mPageChart.init(ui);
    mPageConfig.init(ui);

    setupSlots();   

    QMenu* menu = new QMenu;
    menu->addAction("a");
    menu->addAction("b");
    ui->btnQueryCond->setMenu(menu);

    QCompleter* c = new QCompleter();
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    c->setCompletionColumn(0);
    QStringList keyWords;
    keyWords << "date" << "io" << "amount" << "tags" << "note";
    c->setModel(new QStringListModel(keyWords));
    //ui->editQueryCond->setCompleter(c);

    loadConf();

    mPageAccount.active();
}

MainWindow::~MainWindow()
{    
    saveConf();

    delete ui;
}

void MainWindow::loadConf()
{
    if (QDir().exists(QString::fromAscii(CONF_DB_PATH))) {
        mConfDb->OpenDb(CONF_DB_PATH, false);
    } else {
        mConfDb->OpenDb(CONF_DB_PATH, true);
        QPoint point(QApplication::desktop()->geometry().center() - rect().center());
        mConfDb->Begin();
        mConfDb->SetWindowX(point.x());
        mConfDb->SetWindowY(point.y());
        mConfDb->SetWindowWidth(width());
        mConfDb->SetWindowHeight(height());
        mConfDb->SetLastOpenPath(QDir::homePath().toUtf8().data());
        mConfDb->Commit();
    }
    move(mConfDb->GetWindowX(), mConfDb->GetWindowY());
    resize(mConfDb->GetWindowWidth(), mConfDb->GetWindowHeight());
    mLastOpenPath = QString::fromUtf8(mConfDb->GetLastOpenPath().c_str());
}

void MainWindow::saveConf()
{
    mConfDb->Begin();
    mConfDb->SetWindowX(window()->x());
    mConfDb->SetWindowY(window()->y());
    mConfDb->SetWindowWidth(rect().width());
    mConfDb->SetWindowHeight(rect().height());
    mConfDb->SetLastOpenPath(mLastOpenPath.toStdString());
    mConfDb->Commit();
    mConfDb->CloseDb();
}

void MainWindow::setupSlots()
{
    // global
    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(slotBtnOpenClicked()));
    connect(ui->btnCreate, SIGNAL(clicked()), this, SLOT(slotBtnCreateClicked()));

    // tools
    connect(ui->btnAccount, SIGNAL(clicked()), this, SLOT(slotBtnAccountClicked()));
    connect(ui->btnTag, SIGNAL(clicked()), this, SLOT(slotBtnTagClicked()));
    connect(ui->btnChart, SIGNAL(clicked()), this, SLOT(slotBtnChartClicked()));
    connect(ui->btnConfig, SIGNAL(clicked()), this, SLOT(slotBtnConfigClicked()));
}

void MainWindow::slotBtnOpenClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Cashio Database"),
                mLastOpenPath,
                tr("Cashio Database (*.db)"));
    mLastOpenPath = QFileInfo(fileName).absolutePath();
}

void MainWindow::slotBtnCreateClicked()
{

}

void MainWindow::slotBtnAccountClicked()
{
    mPageAccount.active();
}

void MainWindow::slotBtnTagClicked()
{
    mPageTag.active();
}

void MainWindow::slotBtnChartClicked()
{
    mPageChart.active();
}

void MainWindow::slotBtnConfigClicked()
{
    mPageConfig.active();
}
