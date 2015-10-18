#ifndef BOARDOBJECTBUILDER_H
#define BOARDOBJECTBUILDER_H

#include <QObject>
#include <QQmlListProperty>
#include "boardobjectbuilderstrategy.h"
#include "boardobject.h"

// This class context for different game board object builder strategies
class BoardObjectBuilder : public QObject {
    Q_OBJECT
public:
    // Constructor
    // parent: parent for QObject
    // strategy: stragety to build the level
    // board: pointer to game board object to retrieve properties of board and its objects
    BoardObjectBuilder(QObject *parent,
                                BoardObjectBuilderStrategy* strategy, GameBoard* board);

    // Creates game board objects using current strategy.
    // parent: parent for QObject
    // stageNumber: the number of stage to be created
    // respawnPositions: returns values of respawn position of enemy objects
    QList<BoardObject*> createStageObjects(QObject *parent, unsigned int stageNumer,
                                           QList<int>& respawnPositions);

private:
    // Stores pointer to builder strategy
    BoardObjectBuilderStrategy* builderStrategy;
};

#endif // BOARDOBJECTBUILDER_H
