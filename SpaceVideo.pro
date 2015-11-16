#-------------------------------------------------
#
# Project created by QtCreator 2015-11-15T14:47:58
#
#-------------------------------------------------

QT       += core gui avwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    toolbar.cpp \
    clayout.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    clayout.h

FORMS    += mainwindow.ui \
    toolbar.ui

RESOURCES += \
    assets.qrc
