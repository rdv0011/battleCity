#include "projectileaistrategy.h"
#include "stagemediator.h"
#include "gameboard.h"

ProjectileAIStrategy::ProjectileAIStrategy(QObject* parent, StageMediator* stage,
                                           GameBoard* board):BoardObjectAIStrategy(parent, stage, board) {

}

void ProjectileAIStrategy::objectFired(QString objectId) {
    int positionX, positionY, rotation;
    _board->getObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
    int objectWidth, objectHeight;
    _board->getObjectSizeById(objectId, objectWidth, objectHeight);
    AnimatedBoardObject::MovingDirectionType movingDirection = getMovingDirectionByRotation(rotation);
    switch(movingDirection) {
    case AnimatedBoardObject::MOVING_UP:
        // Gun barrel pointing up
        positionY -= objectHeight / 2 + kStrikingArea;
        break;
    case AnimatedBoardObject::MOVING_RIGHT:
        // Gun barrel pointing to the right
        positionX += objectWidth / 2 + kStrikingArea;
        break;
    case AnimatedBoardObject::MOVING_DOWN:
        // Gun barrel pointing down
        positionY += objectHeight / 2 + kStrikingArea;
        break;
    case AnimatedBoardObject::MOVING_LEFT:
        // Gun barrel pointing to the left
        positionX -= objectWidth / 2 + kStrikingArea;
        break;
    default:
        break;
    }

    int boardWidth, boardHeight;
    _board->getSizeOfBoardInPixels(boardWidth, boardHeight);
    if (positionX >= 0 && positionX <= boardWidth &&
            positionY >= 0 && positionY <= boardHeight &&
        _board->isTileTraversibleWithCoortinates(positionX, positionY)) {
        _stage->sendCreateAnimatedObject(AnimatedBoardObject::TYPE_PROJECTILE, positionX,
                                positionY, rotation, movingDirection);
    }
}

void ProjectileAIStrategy::init() {

}

void ProjectileAIStrategy::advance() {
    QList<QString> list = _board->getObjectIdsByType(AnimatedBoardObject::TYPE_PROJECTILE);
    for(auto projectileObjectId : list) {
        AnimatedBoardObject::MovingDirectionType movingDirection =
                _board->getObjectMovingDirectionById(projectileObjectId);
        bool isHitWall = moveToDirection(projectileObjectId, movingDirection);
        if (isHitWall) {
            _stage->sendRemoveObject(projectileObjectId);
        }
        else {
            QString objectId = getObjectIdHitOther(projectileObjectId, kStrikingArea * 2);
            AnimatedBoardObject::ObjectType type = _board->getTypeByObjectId(objectId);
            // Projectile should not hit another one
            if (objectId.length() &&
                    type != AnimatedBoardObject::TYPE_PROJECTILE) {
                _stage->sendHitObject(projectileObjectId, objectId);
                _stage->sendRemoveObject(projectileObjectId);
            }
        }
    }
}

int ProjectileAIStrategy::getObjectStepInPixels() const {
    return kIncrementStepInPixels * 2;
}
