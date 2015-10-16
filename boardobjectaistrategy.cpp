#include "boardobjectaistrategy.h"
#include "gameboard.h"
#include "stagemediator.h"
#include <QRect>

BoardObjectAIStrategy::BoardObjectAIStrategy(QObject *parent, StageMediator* stage) : QObject(parent),
    _stage(stage) {

}

bool BoardObjectAIStrategy::moveToDirection(QString objectId,
                                                   AnimatedBoardObject::MovingDirectionType direction) {

    if (direction ==  AnimatedBoardObject::MOVING_NONE) return false;

    GameBoard *board = GameBoard::sharedInstance();
    int positionX, positionY, rotation;
    board->getObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
    int positionToCheckX = positionX, positionToCheckY = positionY;
    int objectWidth = 0, objectHeight = 0;
    board->getObjectSizeById(objectId, objectWidth, objectHeight);
    switch(direction) {
    case AnimatedBoardObject::MOVING_UP:
        positionY -= getObjectStepInPixels();
        positionToCheckX += kOffsetToCheck;
        positionToCheckY = positionY;
        rotation = 0;
        break;
    case AnimatedBoardObject::MOVING_DOWN:
        positionY += getObjectStepInPixels();
        positionToCheckX += kOffsetToCheck;
        positionToCheckY = positionY + objectHeight - 1;
        rotation = 180;
        break;
    case AnimatedBoardObject::MOVING_LEFT:
        positionX -= getObjectStepInPixels();
        positionToCheckX = positionX;
        positionToCheckY += kOffsetToCheck;
        rotation = 270;
        break;
    case AnimatedBoardObject::MOVING_RIGHT:
        positionX += getObjectStepInPixels();
        positionToCheckX = positionX + objectWidth - 1;
        positionToCheckY += kOffsetToCheck;
        rotation = 90;
        break;
    default:
        break;
    }
    int boardWidth, boardHeight;
    board->getSizeOfBoardInPixels(boardWidth, boardHeight);
    if (positionToCheckX >= 0 && positionToCheckX <= boardWidth &&
            positionToCheckY >= 0 && positionToCheckY <= boardHeight &&
            board->isTileTraversibleWithCoortinates(positionToCheckX, positionToCheckY)) {
        _stage->sendSetPositionAndRotation(objectId, positionX, positionY, rotation);
        return false;
    }
    return true;
}

QString BoardObjectAIStrategy::getObjectIdHitOther(QString objectId, int strikingRadius) {
    QString retObjectId;
    GameBoard *board = GameBoard::sharedInstance();
    QList<QString> list= board->getObjectIdsByType(AnimatedBoardObject::TYPE_NONE);
    int sourcePositionX = 0, sourcePositionY = 0, sourceRotation = 0;
    board->getObjectPositionAndRotationById(objectId, sourcePositionX,
                                            sourcePositionY, sourceRotation);
    int sourceObjectWidth = 0, sourceObjectHeight = 0;
    board->getObjectSizeById(objectId, sourceObjectWidth, sourceObjectHeight);
    QRect sourceRect(sourcePositionX, sourcePositionY,
                     sourceObjectWidth, sourceObjectHeight);
    sourceRect.setSize(QSize(strikingRadius, strikingRadius));
    sourceRect.translate(sourceObjectWidth / 2, sourceObjectHeight / 2);
    for (auto targetObjectId : list) {
        if (objectId != targetObjectId) {
            int targetPositionX = 0, targetPositionY = 0, targetRotation = 0;
            board->getObjectPositionAndRotationById(targetObjectId, targetPositionX,
                                                    targetPositionY, targetRotation);
            int targetObjectWidth = 0, targetObjectHeight = 0;
            board->getObjectSizeById(targetObjectId, targetObjectWidth, targetObjectHeight);
            QRect targetRect(targetPositionX, targetPositionY,
                             targetObjectWidth, targetObjectHeight);
            if (!sourceRect.intersected(targetRect).isEmpty()) {
                retObjectId = targetObjectId;
                break;
            }
        }
    }
    return retObjectId;
}

AnimatedBoardObject::MovingDirectionType BoardObjectAIStrategy::getMovingDirectionByRotation(int rotation) {
    AnimatedBoardObject::MovingDirectionType movingDirection = AnimatedBoardObject::MOVING_NONE;
    if (rotation < 90) {
        movingDirection = AnimatedBoardObject::MOVING_UP;
    }
    else if (rotation < 180) {
        movingDirection = AnimatedBoardObject::MOVING_RIGHT;
    }
    else if (rotation < 270) {
        movingDirection = AnimatedBoardObject::MOVING_DOWN;
    }
    else {
        movingDirection = AnimatedBoardObject::MOVING_LEFT;
    }
    return movingDirection;
}

int BoardObjectAIStrategy::getObjectStepInPixels() const {
    return kIncrementStepInPixels;
}

void BoardObjectAIStrategy::setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction) {
    GameBoard *board = GameBoard::sharedInstance();
    board->setObjectMovingDirectionById(objectId, direction);
}
