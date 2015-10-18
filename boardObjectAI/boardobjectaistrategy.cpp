#include <QRect>
#include "boardobjectaistrategy.h"
#include "gameboard.h"
#include "stagemediator.h"

BoardObjectAIStrategy::BoardObjectAIStrategy(QObject *parent, StageMediator* stage, GameBoard* board) : QObject(parent),
    _stage(stage),_board(board), _gameLoopIterationCount(0) {

}

bool BoardObjectAIStrategy::moveToDirection(QString objectId,
                                                   AnimatedBoardObject::MovingDirectionType direction) {

    if (direction ==  AnimatedBoardObject::MOVING_NONE) return false;

    int positionX, positionY, rotation;
    _board->getObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
    int objectWidth = 0, objectHeight = 0;
    _board->getObjectSizeById(objectId, objectWidth, objectHeight);
    QPoint positionToCheck1(positionX, positionY);
    QPoint positionToCheck2(positionX, positionY);
    int xOffset = 0, yOffset = 0;
    int tileSize = _board->getTileSize();
    int step = getObjectStepInPixels();
    switch(direction) {
    case AnimatedBoardObject::MOVING_UP:
        xOffset = positionX % tileSize;
        positionY -= step;
        positionToCheck1.setY(positionY);
        positionToCheck1.setX(positionX + kOffsetToCheck);
        positionToCheck2.setX(positionX + objectWidth - kOffsetToCheck);
        positionToCheck2.setY(positionToCheck1.y());
        rotation = 0;
        break;
    case AnimatedBoardObject::MOVING_DOWN:
        xOffset = positionX % tileSize;
        positionY += step;
        positionToCheck1.setY(positionY + objectHeight - 1);
        positionToCheck1.setX(positionX + kOffsetToCheck);
        positionToCheck2.setX(positionX + objectWidth - kOffsetToCheck);
        positionToCheck2.setY(positionToCheck1.y());
        rotation = 180;
        break;
    case AnimatedBoardObject::MOVING_LEFT:
        yOffset = positionY % tileSize;
        positionX -= step;
        positionToCheck1.setY(positionY + kOffsetToCheck);
        positionToCheck1.setX(positionX);
        positionToCheck2.setX(positionX);
        positionToCheck2.setY(positionY + objectHeight - kOffsetToCheck);
        rotation = 270;
        break;
    case AnimatedBoardObject::MOVING_RIGHT:
        yOffset = positionY % tileSize;
        positionX += step;
        positionToCheck1.setY(positionY + kOffsetToCheck);
        positionToCheck1.setX(positionX + objectWidth - 1);
        positionToCheck2.setX(positionToCheck1.x());
        positionToCheck2.setY(positionY + objectHeight - kOffsetToCheck);
        rotation = 90;
        break;
    default:
        break;
    }

    if (xOffset < tileSize / 2) {
        xOffset = -xOffset;
    }
    else {
        xOffset = tileSize - xOffset;
    }

    if (yOffset < tileSize / 2) {
        yOffset = -yOffset;
    }
    else {
        yOffset = tileSize - yOffset;
    }

    int boardWidth, boardHeight;
    _board->getSizeOfBoardInPixels(boardWidth, boardHeight);

    if (positionToCheck1.x() >= 0 && positionToCheck1.x() <= boardWidth &&
            positionToCheck1.y() >= 0 && positionToCheck1.y() <= boardHeight &&
            _board->isTileTraversibleWithCoortinates(positionToCheck1.x(), positionToCheck1.y()) &&
            _board->isTileTraversibleWithCoortinates(positionToCheck2.x(), positionToCheck2.y())) {
        _stage->sendSetPositionAndRotation(objectId, positionX + xOffset,
                                           positionY + yOffset, rotation);
        return false;
    }
    return true;
}

QString BoardObjectAIStrategy::getObjectIdHitOther(QString objectId, int strikingRadius) {
    QString retObjectId;
    QList<QString> list= _board->getObjectIdsByType(AnimatedBoardObject::TYPE_NONE);
    int sourcePositionX = 0, sourcePositionY = 0, sourceRotation = 0;
    _board->getObjectPositionAndRotationById(objectId, sourcePositionX,
                                            sourcePositionY, sourceRotation);
    int sourceObjectWidth = 0, sourceObjectHeight = 0;
    _board->getObjectSizeById(objectId, sourceObjectWidth, sourceObjectHeight);
    QRect sourceRect(sourcePositionX, sourcePositionY,
                     sourceObjectWidth, sourceObjectHeight);
    sourceRect.setSize(QSize(strikingRadius, strikingRadius));
    sourceRect.translate(sourceObjectWidth / 2, sourceObjectHeight / 2);
    for (auto targetObjectId : list) {
        if (objectId != targetObjectId) {
            int targetPositionX = 0, targetPositionY = 0, targetRotation = 0;
            _board->getObjectPositionAndRotationById(targetObjectId, targetPositionX,
                                                    targetPositionY, targetRotation);
            int targetObjectWidth = 0, targetObjectHeight = 0;
            _board->getObjectSizeById(targetObjectId, targetObjectWidth, targetObjectHeight);
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
    _stage->sendSetObjectMovingDirectionById(objectId, direction);
}

void BoardObjectAIStrategy::advance() {
    _gameLoopIterationCount++;
}
