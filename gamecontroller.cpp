#include <QTimer>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gamecontroller.h"
#include "gameboard.h"
#include "stagemediator.h"

GameController::GameController(QObject *parent) : QObject(parent),
    _stage(nullptr), _frameTimer(nullptr) {

    _stage = new StageMediator(this);
    if (_stage) {
        _stage->setGameControllerDelegate(this);
        _frameTimer = new QTimer(this);
        if (_frameTimer) {
            connect(_frameTimer, SIGNAL(timeout()), SLOT(nextFrame()));
            initWithStage(1);
        }
    }
}


void GameController::initWithStage(unsigned int stageNumber) {
    _stage->sendInit(stageNumber, 20, 2);

    QList<AnimatedBoardObject*> list = _stage->getGameBoard()->getBoardObjectsWithType(AnimatedBoardObject::TYPE_USERTANK);
    if (list.count()) {
        AnimatedBoardObject *userObject = list.first();
        _userRespawnPoint = QPoint(userObject->getPositionX(),
                                   userObject->getPositionY());
    }
    _frameTimer->start(kNextFrameTimeout);
    QTimer::singleShot(0, this, SLOT(initFrame()));
}

GameBoard* GameController::getGameBoard() const {
    return _stage->getGameBoard();
}

void GameController::nextFrame() {
    _stage->nextFrame();
}

void GameController::initFrame() {
    _stage->initFrame();
}

// GameControllerProtocol
void GameController::objectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type) {
    Q_UNUSED(objectId)
    Q_UNUSED(type)
}

void GameController::objectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type) {

    Q_UNUSED(objectId)

    // End game cases handler
    GameBoard* board = _stage->getGameBoard();
    switch(type) {
    case AnimatedBoardObject::TYPE_ENEMYTANK:
    {
        _stage->sendAddOneFrag("");
        if (board->getMaxFragsCount() > board->getFragsCount()) {
            QList<QString> list = board->getObjectIdsByType(AnimatedBoardObject::TYPE_ENEMYTANK);
            if (list.count() < board->getRespawnPointsView().count()) {
                QList<QPoint*> respawnPoints = board->getRespawnPointsView();
                if (respawnPoints.count()) {
                    int randomIndex = qrand() % respawnPoints.count();
                    QPoint *pt = respawnPoints[randomIndex];
                    _stage->sendCreateAnimatedObject(AnimatedBoardObject::TYPE_ENEMYTANK, pt->x(),
                                                     pt->y(), 0, AnimatedBoardObject::MOVING_UP);
                }
            }
        }
        else {
            initWithStage(1);
        }
    }
        break;
    case AnimatedBoardObject::TYPE_USERTANK:
    {
        _stage->sendRemoveOneLife("");
        if (board->getLifesCount() > 0) {
            _stage->sendCreateAnimatedObject(AnimatedBoardObject::TYPE_USERTANK, _userRespawnPoint.x(),
                                             _userRespawnPoint.y(), 0, AnimatedBoardObject::MOVING_NONE);
        }
        else {
            initWithStage(1);
        }
    }
        break;
    case AnimatedBoardObject::TYPE_USERBASE:
        // In this case user loses and we should end game immidiately
        break;
    default:
        break;
    }
}
