#include "PageChart.h"
#include "ui_MainWindow.h"
#include "sqt/UiHelper.hpp"
using namespace sqt;

PageChart::PageChart()
{
}

PageChart::~PageChart()
{

}

void PageChart::init(const Ui::MainWindow *_ui)
{
    ui = _ui;

    connect(ui->btnDraw, SIGNAL(clicked()), this, SLOT(drawSomeThing()));
}

void PageChart::active()
{
    UiHelper::switchStackPage(ui->stackedWidgetToolbarExt, 2);
    UiHelper::switchStackPage(ui->stackedWidgetMoreTool, 2);
    UiHelper::switchStackPage(ui->stackedWidgetContent, 2);

    ui->stackedWidgetMoreTool->setVisible(true);

    drawSomeThing();
}

void PageChart::saveState()
{

}

void PageChart::drawSomeThing()
{
    int w = ui->graphicsView->width() - 10;
    int h = ui->graphicsView->height() - 10;
    QGraphicsScene* scene = new QGraphicsScene(0, 0, w, h);
    scene->addText("Hello, world!")->setPos(0, 0);

    QPoint po(0, h);

    QPainterPath path;

    path.moveTo(po);
    path.lineTo(po.x() + w-10, po.y());
    path.moveTo(po);
    path.lineTo(po.x(),po.y() - h+10);
    for (int i = 10; i < 500; i+= 50)
    {
        QPoint pa(po.x() + i, po.y());
        QPoint pb(pa);
        pb.setY(pb.y() - 200);
        path.moveTo(pa);
        path.lineTo(pb);
    }

    QFont font(ui->graphicsView->font());
    //font.setStyleStrategy(QFont::PreferQuality);
    path.addText(10, 10, font, "你好fine");
    scene->addPath(path);

    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
}
