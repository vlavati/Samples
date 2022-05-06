TARGET = tronic
TEMPLATE = app

QT += qml network quick

SOURCES += main.cpp

RESOURCES += \
    tronic.qrc

OTHER_FILES += \
    qml/*.qml \
    qml/*.js

target.path = /opt/tronic

INSTALLS += target
