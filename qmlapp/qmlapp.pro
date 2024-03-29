TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    cproductsviewmodel.cpp \
    ceditviewmodel.cpp \
    cviewmodelfactory.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    cproductsviewmodel.h \
    ceditviewmodel.h \
    cviewmodelfactory.h
