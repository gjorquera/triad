QT += opengl
TEMPLATE = app
TARGET = Triad
DESTDIR = ../../../bin

include(../../qworkbench.pri)

SOURCES += main.cpp \
    mainwindow.cpp \
    widgets/displaywidget.cpp
HEADERS += mainwindow.h \
    widgets/displaywidget.h
FORMS += mainwindow.ui

