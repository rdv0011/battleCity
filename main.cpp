#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "gamecontroller.h"
#include "gameboard.h"
#include "tile.h"
#include "animatedboardobject.h"
#include "stagemediator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    int retCode = 0;

    try {
        GameController *game = new GameController(&app);

        qmlRegisterType<Tile>();
        qmlRegisterType<AnimatedBoardObject>();
        qmlRegisterType<BoardObject>();

        GameBoard* gameBoard = game->getGameBoard();
        engine.rootContext()->setContextProperty("gameBoard", gameBoard);

        engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

        retCode = app.exec();
    }
    catch(const std::bad_alloc&) {
        // There is no references to external resources yet, so show message and exit
        qDebug("Not enough memory!");
    }

    return retCode;
}
