#ifndef STAGEMEDIATOR_H
#define STAGEMEDIATOR_H

#include <QObject>
#include "animatedboardobject.h"

class BoardObjectAIContext;
class GameController;
class GameBoard;
class StageMediator : public QObject
{
    Q_OBJECT
public:
    StageMediator(QObject *parent);

    void sendMovingDirectionChanged(QString objectId, AnimatedBoardObject::MovingDirectionType direction);

    void sendSetPositionAndRotation(QString objectId, int positionX, int positionY, int rotation);

    void sendControlKeyPressed(QString objectId, int key);

    void sendObjectFired(QString objectId);

    void sendHitObject(QString sourceObjectId, QString targetObjectId);

    void sendObjectWillRemove(QString objectId);

    void setAIContexts(QList<BoardObjectAIContext*>& contexts);

    void setGameBoard(GameBoard* board);

    void setGameController(GameController *controller);

private:
    QList<BoardObjectAIContext*> _contexts;
    GameController *_controller;
    GameBoard* _board;
};

#endif // STAGEMEDIATOR_H
