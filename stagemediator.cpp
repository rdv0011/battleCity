#include "stagemediator.h"
#include "gameboard.h"
#include "boardobjectaicontext.h"
#include "gamecontroller.h"

StageMediator::StageMediator(QObject *parent) : QObject(parent) {

}

void StageMediator::setAIContexts(QList<BoardObjectAIContext*>& contexts) {
    _contexts = contexts;
}

void StageMediator::setGameBoard(GameBoard* board) {
    _board = board;
}

void StageMediator::setGameController(GameController *controller) {
    _controller = controller;
}

void StageMediator::sendMovingDirectionChanged(QString objectId, AnimatedBoardObject::MovingDirectionType direction) {
    for(auto context : _contexts) {
        context->setMovingDirection(objectId, direction);
    }
}

void StageMediator::sendSetPositionAndRotation(QString objectId, int positionX,
                                               int positionY, int rotation) {
    GameBoard::sharedInstance()->setObjectPositionAndRotationById(objectId, positionX, positionY, rotation);
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

void StageMediator::sendObjectWillRemove(QString objectId) {
    _controller->objectWillRemove(objectId);
}
