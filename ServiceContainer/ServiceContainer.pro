QT -= core
QT -= gui

TARGET = ServiceContainerTest

CONFIG += console

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    model.h \
    cservicecontainer.h \
    internal.h \
    cservicecreator.h \
    di.h \
    dimodule.h
