#include "boardobjectbuilder.h"
#include "tile.h"
#include "animatedboardobject.h"
#include "boardobjectbuilderstrategyeasy.h"
#include <QFile>
#include <QtDebug>

BoardObjectBuilder::BoardObjectBuilder(QObject *parent,
                                       BoardObjectBuilderStrategy* strategy, GameBoard* board) : QObject(parent),
builderStrategy(strategy) {
    // Create instance of building strategy
    if (!builderStrategy) {
        builderStrategy = new BoardObjectBuilderStrategyEasy(this, board);
    }
    // Build the chain of different game objects
    AnimatedBoardObject* animatedObject = new AnimatedBoardObject(this);
    animatedObject->setNext(new Tile(this));
    builderStrategy->setChainOfObjects(animatedObject);
}

QList<BoardObject*> BoardObjectBuilder::createStageObjects(QObject *parent,
                                                           unsigned int stageNumer,
                                                           QList<int>& respawnPositions) {
    QList<BoardObject*> boardObjects;
    // Open the map file
    QFile mapFile(QString(":/data/level%1.dat").arg(stageNumer));
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        // It might be worth to show dialog box
        qDebug().nospace() << qPrintable(QString("Error: map file with number %1 not found.").arg(stageNumer));
        return QList<BoardObject*>();
    }
    QTextStream textStream(&mapFile);
    if (builderStrategy) {
        boardObjects = builderStrategy->createStageObjects(parent, textStream, respawnPositions);
    }
    mapFile.close();
    return boardObjects;
}
