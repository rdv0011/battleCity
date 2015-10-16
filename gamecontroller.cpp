#include <QTimer>
#include "gamecontroller.h"
#include "gameboard.h"
#include "stagemediator.h"
#include "tankaistrategy.h"
#include "boardobjectaicontext.h"
#include "projectileaistrategy.h"
#include "userbaseaistrategy.h"

GameController::GameController(QObject *parent) : QObject(parent) {
}


void GameController::initWithStage(unsigned int stageNumber) {
    _gameBoard = GameBoard::sharedInstance(this);
    _stage = new StageMediator(this);
    QList<BoardObjectAIStrategy*> strategyList;
    strategyList.append(new TankAIStrategy(this, _stage));
    strategyList.append(new ProjectileAIStrategy(this, _stage));
    strategyList.append(new UserBaseAIStrategy(this, _stage));
    _contexts.append(new BoardObjectAIContext(this, strategyList, _stage));
    _stage->setAIContexts(_contexts);
    _stage->setGameBoard(_gameBoard);
    _stage->setGameController(this);
    _gameBoard->init(_stage, stageNumber);
    _gameBoard->createFragObjectsByNumber(20);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(nextFrame()));
    timer->start(kNextFrameTimeout);

    QTimer::singleShot(0, this, SLOT(aiInit()) );
}

GameBoard* GameController::getGameBoard() const {
    return this->_gameBoard;
}

void GameController::nextFrame() {
    for(auto context : _contexts) {
        context->advance();
    }
}

void GameController::aiInit() {
    for(auto context : _contexts) {
        context->init();
    }
}

void GameController::objectWillRemove(QString objectId) {
}
