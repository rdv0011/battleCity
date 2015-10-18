#ifndef BOARDOBJECTBUILDERSTRATEGY_H
#define BOARDOBJECTBUILDERSTRATEGY_H

#include <QObject>
#include <QQmlListProperty>
#include <QTextStream>
#include <memory>

class BoardObject;
class GameBoard;
// This class declares base interface for builder strategy.
class BoardObjectBuilderStrategy : public QObject {
    Q_OBJECT
public:
    // Constructor
    BoardObjectBuilderStrategy(QObject *parent, GameBoard*);
    // Set next ojbect in the chain.
    void setChainOfObjects(BoardObject *chain) {
        _chainOfObjects = chain;
    }
    // Returns game board objects
    // textStream: stream of text file with stage data
    // respawnPositions: returns the list of respawn positions of enemies
    virtual QList<BoardObject*> createStageObjects(QObject *parent,
                                                   QTextStream& textStream,
                                                   QList<int>& respawnPositions) = 0;
protected:
    // Store pointer to next object in the chain.
    BoardObject* _chainOfObjects;
    // Pointer to game board object.
    GameBoard* _board;
};

#endif // BOARDOBJECTBUILDERSTRATEGY_H
