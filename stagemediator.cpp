#include "stagemediator.h"
#include "gameboard.h"
#include "boardobjectaicontext.h"
#include "gamecontroller.h"
#include "tankaistrategy.h"
#include "projectileaistrategy.h"
#include "userbaseaistrategy.h"

StageMediator::StageMediator(QObject *parent) : QObject(parent) {
    _board = new GameBoard(this);
    QList<BoardObjectAIStrategy*> strategyList;
    try {
        if (auto strategy = new TankAIStrategy(this, this, _board)) {
            strategyList.append(strategy);
        }
        if (auto strategy = new ProjectileAIStrategy(this, this, _board)) {
            strategyList.append(strategy);
        }
        if (auto strategy = new UserBaseAIStrategy(this, this, _board)) {
            strategyList.append(strategy);
        }
        if (auto context = new BoardObjectAIContext(this, strategyList, this)) {
            _contexts.append(context);
        }
    }
    catch(std::bad_alloc&) {
        qDebug("Not enough memory!");
        throw;
    }
}

StageMediator::~StageMediator() {

}

void StageMediator::sendInit(int stageNumber, int fragsCount, int lifesCount) {
    _board->init(this, stageNumber);
    _board->createFragObjectsByNumber(fragsCount);
    _board->setLifesCount(lifesCount);
}

void StageMediator::setGameControllerDelegate(GameControllerProtocol *controllerDelegate) {
    _controllerDelegate = controllerDelegate;
}

void StageMediator::sendMovingDirectionChanged(QString objectId,
                                               AnimatedBoardObject::MovingDirectionType direction) {
    for(auto context : _contexts) {
        context->setMovingDirection(objectId, direction);
    }
}

void StageMediator::sendSetPositionAndRotation(QString objectId, int positionX,
                                               int positionY, int rotation) {
    _board->setObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
}

void StageMediator::sendControlKeyPressed(QString objectId, int key) {
    for(auto context : _contexts) {
        context->controlKeyPressed(objectId, key);
    }
}

void StageMediator::sendObjectFired(QString objectId) {
    for(auto context : _contexts) {
        context->objectFired(objectId);
    }
}

void StageMediator::sendHitObject(QString sourceObjectId, QString targetObjectId) {
    for(auto context : _contexts) {
        context->objectHitByObject(targetObjectId, sourceObjectId);
    }
}

void StageMediator::sendRemoveObject(const QString& objectId) {
    if (objectId.length() && _board) {
        _board->removeObject(objectId);
    }
}

void StageMediator::sendObjectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type) {
    if (_controllerDelegate) {
        _controllerDelegate->objectDidCreate(objectId, type);
    }
    for(auto context : _contexts) {
        context->objectDidCreate(objectId, type);
    }
}

void StageMediator::sendObjectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type) {
    if (_controllerDelegate) {
        _controllerDelegate->objectDidRemove(objectId, type);
    }
    for(auto context : _contexts) {
        context->objectDidRemove(objectId, type);
    }
}

void StageMediator::sendSetObjectMovingDirectionById(const QString& objectId,
                                  AnimatedBoardObject::MovingDirectionType movingDirection) {
    if (objectId.length() && _board) {
        _board->setObjectMovingDirectionById(objectId, movingDirection);
    }
}

void StageMediator::sendCreateAnimatedObject(AnimatedBoardObject::ObjectType type,
                                             int positionX,
                                             int positionY,
                                             int rotation,
                                             AnimatedBoardObject::MovingDirectionType movingDirection) {
    if (_board) {
        _board->createAnimatedObject(type, positionX,
                                     positionY, rotation, movingDirection);
    }
}

void StageMediator::sendAddOneFrag(const QString& userId) {
    if (_board) {
        _board->addOneFrag(userId);
    }
}

void StageMediator::sendRemoveOneLife(const QString& userId) {
    if (_board) {
        _board->removeOneLife(userId);
    }
}

GameBoard* StageMediator::getGameBoard() const {
    return this->_board;
}


void StageMediator::initFrame() {
    for(auto context : _contexts) {
        context->init();
    }
}

void StageMediator::nextFrame() {
    for(auto context : _contexts) {
        context->advance();
    }
}
