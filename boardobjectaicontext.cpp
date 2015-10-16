#include "boardobjectaicontext.h"
#include "stagemediator.h"
#include "boardobjectaistrategy.h"
#include "tankaistrategy.h"
#include "projectileaistrategy.h"

BoardObjectAIContext::BoardObjectAIContext(QObject *parent, QList<BoardObjectAIStrategy*> strategies,
                                           StageMediator* stage) : QObject(parent), _strategies(strategies), _stage(stage) {

}

void BoardObjectAIContext::setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction) {
    for(auto strategy: _strategies) {
        strategy->setMovingDirection(objectId, direction);
    }
}

void BoardObjectAIContext::controlKeyPressed(QString objectId, int key) {
    for(auto strategy: _strategies) {
        if (dynamic_cast<TankAIStrategy*>(strategy)) {
            strategy->controlKeyPressed(objectId, key);
        }
    }
}

void BoardObjectAIContext::objectFired(QString objectId) {
    for(auto strategy: _strategies) {
        if (dynamic_cast<ProjectileAIStrategy*>(strategy)) {
            strategy->objectFired(objectId);
        }
    }
}

void BoardObjectAIContext::objectHitByObject(QString objectId, QString byObjectId) {
    for(auto strategy: _strategies) {
        if (dynamic_cast<TankAIStrategy*>(strategy)) {
            strategy->objectHitByObject(objectId, byObjectId);
        }
    }
}

void BoardObjectAIContext::advance() {
    for(auto strategy: _strategies) {
        strategy->advance();
    }
}

void BoardObjectAIContext::init() {
    for(auto strategy: _strategies) {
        strategy->init();
    }
}
