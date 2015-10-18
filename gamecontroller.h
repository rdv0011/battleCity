#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QPoint>

#include "gamecontrollerprotocol.h"
#include "animatedboardobject.h"

class QTimer;
class GameBoard;
class StageMediator;
class QQmlApplicationEngine;
// This class declares interface fo entry point of the game.
// General controller of the game. Start/ends game, propagate changes to control panel.
class GameController : public QObject, public GameControllerProtocol {
    // The timeout for the next iteration of game loop
    const int kNextFrameTimeout = 30;

    Q_OBJECT
public:
    // Constructor
    explicit GameController(QObject *parent = 0);
    // Initialize the stage with number. Entry point for cratetion objects of the game.
    void initWithStage(unsigned int stageNumber);
    // Returns game board object
    GameBoard* getGameBoard() const;
    // GameControllerProtocol
    virtual void objectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type);
    virtual void objectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type);

public slots:
    // Timer slots for game loop
    void nextFrame();
    // Called onceto initilize underliing stuff
    void initFrame();

private:
    // Pointer to stage object
    StageMediator* _stage;
    // Game loop timer
    QTimer* _frameTimer;
    // Stores respawn point of the user's object
    QPoint _userRespawnPoint;
};

#endif // GAMECONTROLLER_H
