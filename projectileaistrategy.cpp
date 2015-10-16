#include "projectileaistrategy.h"
#include "stagemediator.h"
#include "gameboard.h"

ProjectileAIStrategy::ProjectileAIStrategy(QObject* parent, StageMediator* stage):BoardObjectAIStrategy(parent, stage) {

}

void ProjectileAIStrategy::objectFired(QString objectId) {
    GameBoard *board = GameBoard::sharedInstance();
    int positionX, positionY, rotation;
    board->getObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
    int objectWidth, objectHeight;
    board->getObjectSizeById(objectId, objectWidth, objectHeight);
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
    board->getSizeOfBoardInPixels(boardWidth, boardHeight);
    if (positionX >= 0 && positionX <= boardWidth &&
            positionY >= 0 && positionY <= boardHeight &&
        board->isTileTraversibleWithCoortinates(positionX, positionY)) {
        board->createAnimatedObject(AnimatedBoardObject::TYPE_PROJECTILE, positionX,
                                positionY, rotation, movingDirection);
    }
}

void ProjectileAIStrategy::init() {

}

void ProjectileAIStrategy::advance() {
    GameBoard *board = GameBoard::sharedInstance();
    QList<QString> list = board->getObjectIdsByType(AnimatedBoardObject::TYPE_PROJECTILE);
    for(auto projectileObjectId : list) {
        AnimatedBoardObject::MovingDirectionType movingDirection =
                board->getObjectMovingDirectionById(projectileObjectId);
        bool isHitWall = moveToDirection(projectileObjectId, movingDirection);
        if (isHitWall) {
            board->removeObject(projectileObjectId);
        }
        else {
            QString objectId = getObjectIdHitOther(projectileObjectId, kStrikingArea * 2);
            if (objectId.length()) {
                _stage->sendHitObject(projectileObjectId, objectId);
                board->removeObject(projectileObjectId);
            }
        }
    }
}

int ProjectileAIStrategy::getObjectStepInPixels() const {
    return kIncrementStepInPixels * 2;
}
