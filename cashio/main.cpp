#include <QtGui>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    QApplication app(argc, argv);
    MainWindow wnd;
    wnd.show();    
    return app.exec();
}
