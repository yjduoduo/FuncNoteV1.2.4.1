#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T10:25:05
#
#-------------------------------------------------

QT       += core gui

TARGET = FuncNote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    version.h \
    lcd.h

FORMS    += mainwindow.ui

LIBS+= -lShell32

RC_FILE = myapp.rc
