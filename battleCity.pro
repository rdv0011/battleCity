TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    boardobject.cpp \
    tile.cpp \
    boardobjectbuilder.cpp \
    boardobjectbuilderstrategyeasy.cpp \
    boardobjectbuilderstrategy.cpp \
    gameboard.cpp \
    animatedboardobject.cpp \
    boardobjectaistrategy.cpp \
    projectileaistrategy.cpp \
    userbaseaistrategy.cpp \
    tankaistrategy.cpp \
    boardobjectaicontext.cpp \
    stagemediator.cpp \
    gamecontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    boardobject.h \
    tile.h \
    boardobjectbuilder.h \
    boardobjectbuilderstrategy.h \
    boardobjectbuilderstrategyeasy.h \
    gameboard.h \
    animatedboardobject.h \
    boardobjectaistrategy.h \
    projectileaistrategy.h \
    userbaseaistrategy.h \
    tankaistrategy.h \
    boardobjectaicontext.h \
    stagemediator.h \
    gamecontroller.h

