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

    GameController *game = new GameController(&app);
    game->initWithStage(1);

    qmlRegisterType<Tile>();
    qmlRegisterType<AnimatedBoardObject>();
    qmlRegisterType<BoardObject>();

    GameBoard* gameBoard = game->getGameBoard();
    engine.rootContext()->setContextProperty("gameBoard", gameBoard);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
