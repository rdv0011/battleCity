#include <QSound>
#include <QTimer>

#include "tankaistrategy.h"
#include "stagemediator.h"
#include "gameboard.h"
#include "resourcesound.h"

TankAIStrategy::TankAIStrategy(QObject* parent, StageMediator* stage, GameBoard* board):BoardObjectAIStrategy(parent, stage, board),
_lastFiredObject(AnimatedBoardObject::TYPE_NONE),
  _userMovingSound(nullptr), _userMovingSoundTimer(nullptr),
  _isUserTankFiring(false) {
    _userMovingSound = new QSound(ResourceSound(kUserMovingFileName).getSoundFileName(), this);
}

void TankAIStrategy::controlKeyPressed(QString objectId, int key) {
    if (_board->getTypeByObjectId(objectId) == AnimatedBoardObject::TYPE_USERTANK &&
            Qt::Key_Space == key) {
        _isUserTankFiring = true;
    }
}

void TankAIStrategy::objectTypeDidCreate(QString objectId, AnimatedBoardObject::ObjectType type) {
    if (type == AnimatedBoardObject::TYPE_PROJECTILE &&
            _lastFiredObject == AnimatedBoardObject::TYPE_ENEMYTANK) {
        _lastFiredObject = AnimatedBoardObject::TYPE_NONE;
        _enemyProjectiles.append(objectId);
    }
}

void TankAIStrategy::objectTypeDidRemove(QString objectId, AnimatedBoardObject::ObjectType type) {

    Q_UNUSED(type)

    _enemyProjectiles.removeOne(objectId);
}

void TankAIStrategy::objectHitByObject(QString objectId, QString byObjectId) {
    AnimatedBoardObject::ObjectType type = _board->getTypeByObjectId(objectId);
    if ((type == AnimatedBoardObject::TYPE_USERTANK &&
         _enemyProjectiles.contains(byObjectId)) ||
            (type == AnimatedBoardObject::TYPE_ENEMYTANK &&
             !_enemyProjectiles.contains(byObjectId)) ||
            type == AnimatedBoardObject::TYPE_USERBASE) {
        int positionX, positionY, rotation;
        _board->getObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
        _stage->sendRemoveObject(objectId);
        // Show explosion where the tank was
        _stage->sendCreateAnimatedObject(AnimatedBoardObject::TYPE_EXPLOSION, positionX,
                                positionY, rotation, AnimatedBoardObject::MOVING_NONE);
        ResourceSound::play(kExplosionFileName);
    }
}

void TankAIStrategy::init() {
    QList<QString> tanksList = _board->getObjectIdsByType(AnimatedBoardObject::TYPE_ENEMYTANK);
    for(auto tankId : tanksList) {
        int positionX, positionY, rotation;
        _board->getObjectPositionAndRotationById(tankId, positionX, positionY, rotation);
        AnimatedBoardObject::MovingDirectionType movingDirection = getMovingDirectionByRotation(rotation);
        setMovingDirection(tankId, movingDirection);
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

    BoardObjectAIStrategy::advance();

    QList<QString> tanksList = _board->getObjectIdsByType(AnimatedBoardObject::TYPE_ENEMYTANK);
    for(auto tankId : tanksList) {
        AnimatedBoardObject::MovingDirectionType movingDirection = _board->getObjectMovingDirectionById(tankId);
        if (moveToDirection(tankId, movingDirection)) {
            setMovingDirection(tankId, getMovingDirectionNotEqualTo(movingDirection));
        }
        if (qrand() % 50 == 0) {
            _lastFiredObject = AnimatedBoardObject::TYPE_ENEMYTANK;
            _stage->sendObjectFired(tankId);
            ResourceSound::play(kShotSoundFileName);
        }
    }
    QList<QString> userTankList = _board->getObjectIdsByType(AnimatedBoardObject::TYPE_USERTANK);
    if (userTankList.count()) {
        QString userTankId = userTankList.first();

        // If user pressed control key propagate fire event to mediator
        // Use constant to tune firing speed
        if (_isUserTankFiring &&
                _gameLoopIterationCount % kFiringSpeedFactor == 0) {
            _isUserTankFiring = false;
            _stage->sendObjectFired(userTankId);
            ResourceSound::play(kShotSoundFileName);
        }

        AnimatedBoardObject::MovingDirectionType movingDirection = _board->getObjectMovingDirectionById(userTankId);
        if (movingDirection != AnimatedBoardObject::MOVING_NONE) {
            moveToDirection(userTankId, movingDirection);

            if (_userMovingSound->isFinished()) {
                _userMovingSound->play();
            }

            if (_userMovingSoundTimer) {
                delete _userMovingSoundTimer;
                _userMovingSoundTimer = nullptr;
            }

            // Start timer to stop the moving sound
            _userMovingSoundTimer = new QTimer(this);
            connect(_userMovingSoundTimer, SIGNAL(timeout()),
                        SLOT(stopUserMovingSound()));
            _userMovingSoundTimer->start(100);
            _userMovingSoundTimer->setSingleShot(true);
        }
    }
}

void TankAIStrategy::stopUserMovingSound() {
    if (_userMovingSound &&
            !_userMovingSound->isFinished()) {
        _userMovingSound->stop();
    }
}
