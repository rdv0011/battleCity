#include "tankaistrategy.h"
#include "stagemediator.h"
#include "gameboard.h"

TankAIStrategy::TankAIStrategy(QObject* parent, StageMediator* stage):BoardObjectAIStrategy(parent, stage) {
}

void TankAIStrategy::controlKeyPressed(QString objectId, int key) {
    GameBoard *board = GameBoard::sharedInstance();
    if (board->getTypeByObjectId(objectId) == AnimatedBoardObject::TYPE_USERTANK &&
            Qt::Key_Space == key) {
        _stage->sendObjectFired(objectId);
    }
}

void TankAIStrategy::objectHitByObject(QString objectId, QString byObjectId) {
    GameBoard *board = GameBoard::sharedInstance();
    AnimatedBoardObject::ObjectType type = board->getTypeByObjectId(objectId);
    if (type == AnimatedBoardObject::TYPE_USERTANK) {

    }
    else if (type == AnimatedBoardObject::TYPE_ENEMYTANK) {
        _stage->sendObjectWillRemove(objectId);
        board->removeObject(objectId);
    }
}

void TankAIStrategy::init() {
    GameBoard *board = GameBoard::sharedInstance();
    QList<QString> tanksList = board->getObjectIdsByType(AnimatedBoardObject::TYPE_ENEMYTANK);
    for(auto tankId : tanksList) {
        int positionX, positionY, rotation;
        board->getObjectPositionAndRotationById(tankId, positionX, positionY, rotation);
        AnimatedBoardObject::MovingDirectionType movingDirection = getMovingDirectionByRotation(rotation);
        board->setObjectMovingDirectionById(tankId, movingDirection);
    }
}

AnimatedBoardObject::MovingDirectionType getMovingDirectionNotEqualTo(AnimatedBoardObject::MovingDirectionType direction) {
    AnimatedBoardObject::MovingDirectionType newMovingDirection = direction;
    for(int i = 0; i < 10 && newMovingDirection == direction; i++) {
        int directionInt = (int)AnimatedBoardObject::MOVING_NONE;
        int newDirectionInt = qrand() % directionInt;
        newMovingDirection = (AnimatedBoardObject::MovingDirectionType)newDirectionInt;
    }
    return newMovingDirection;
}


void TankAIStrategy::advance() {
    GameBoard *board = GameBoard::sharedInstance();
    QList<QString> tanksList = board->getObjectIdsByType(AnimatedBoardObject::TYPE_ENEMYTANK);
    for(auto tankId : tanksList) {
        AnimatedBoardObject::MovingDirectionType movingDirection = board->getObjectMovingDirectionById(tankId);
        if (moveToDirection(tankId, movingDirection)) {
            board->setObjectMovingDirectionById(tankId, getMovingDirectionNotEqualTo(movingDirection));
        }
        if (qrand() % 50 == 0) {
            _stage->sendObjectFired(tankId);
        }
    }
    QList<QString> userTankList = board->getObjectIdsByType(AnimatedBoardObject::TYPE_USERTANK);
    if (userTankList.count()) {
        QString userTankId = userTankList.first();
        AnimatedBoardObject::MovingDirectionType movingDirection = board->getObjectMovingDirectionById(userTankId);
        if (movingDirection != AnimatedBoardObject::MOVING_NONE) {
            moveToDirection(userTankId, movingDirection);
        }
    }
}
