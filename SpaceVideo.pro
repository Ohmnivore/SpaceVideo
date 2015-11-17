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
    options.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    options.h

FORMS    += mainwindow.ui \
    toolbar.ui \
    options.ui

RESOURCES += \
    assets.qrc

LIBS += "C:/Qt/5.5/msvc2013/lib/VLCQtCore.lib"
LIBS += "C:/Qt/5.5/msvc2013/lib/VLCQtWidgets.lib"
