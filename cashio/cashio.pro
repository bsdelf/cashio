#-------------------------------------------------
#
# Project created by QtCreator 2011-08-22T15:07:11
#
#-------------------------------------------------

QT       += core gui

TARGET = cashio
TEMPLATE = app

# You should put sqlite3.h into "include",
# and sqlite3.lib into "lib" for Windows.
win32 {
    INCLUDEPATH += include
    LIBS += $$_PRO_FILE_PWD_\lib\sqlite3.lib"
}

# You should have sqlite3 installed under /usr .
unix {
    LIBS += -lsqlite3
}

SOURCES += main.cpp\
        MainWindow.cpp \
    WidgetDbBar.cpp \
    WidgetGraphBar.cpp \
    CashDb.cpp \
    TableRendererCash.cpp

HEADERS  += MainWindow.h \
    WidgetDbBar.h \
    WidgetGraphBar.h \
    DbDef.h \
    CashDb.h \
    SqliteBase.h \
    TableRendererCash.h

FORMS    += MainWindow.ui \
    WidgetDbBar.ui \
    WidgetGraphBar.ui
