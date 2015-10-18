TEMPLATE = app

QT += qml quick widgets multimedia
CONFIG += c++11

SOURCES += main.cpp \
    boardObject/boardobject.cpp \
    boardObject/tile.cpp \
    boardObjectBuilder/boardobjectbuilder.cpp \
    boardObjectBuilder/boardobjectbuilderstrategyeasy.cpp \
    boardObjectBuilder/boardobjectbuilderstrategy.cpp \
    gameboard.cpp \
    boardObject/animatedboardobject.cpp \
    boardObjectAI/boardobjectaistrategy.cpp \
    boardObjectAI/projectileaistrategy.cpp \
    boardObjectAI/userbaseaistrategy.cpp \
    boardObjectAI/tankaistrategy.cpp \
    boardObjectAI/boardobjectaicontext.cpp \
    stagemediator.cpp \
    gamecontroller.cpp \
    utils/resourcesound.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    boardObject/boardobject.h \
    boardObject/tile.h \
    boardObjectBuilder/boardobjectbuilder.h \
    boardObjectBuilder/boardobjectbuilderstrategy.h \
    boardObjectBuilder/boardobjectbuilderstrategyeasy.h \
    gameboard.h \
    boardObject/animatedboardobject.h \
    boardObjectAI/boardobjectaistrategy.h \
    boardObjectAI/projectileaistrategy.h \
    boardObjectAI/userbaseaistrategy.h \
    boardObjectAI/tankaistrategy.h \
    boardObjectAI/boardobjectaicontext.h \
    stagemediator.h \
    gamecontroller.h \
    gamecontrollerprotocol.h \
    utils/resourcesound.h

INCLUDEPATH += boardObject boardObjectAI boardObjectBuilder utils
