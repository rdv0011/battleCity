#ifndef STAGEMEDIATOR_H
#define STAGEMEDIATOR_H

#include <QObject>
#include "animatedboardobject.h"

class BoardObjectAIContext;
class GameControllerProtocol;
class GameBoard;
// This class is mediator between different classes in the game.
// Transfers messages between game board object, AI strategies, game board, game controller
class StageMediator : public QObject
{
    Q_OBJECT
public:
    // Constructor
    explicit StageMediator(QObject *parent = 0);
    // Destructor
    ~StageMediator();
    // Send initialize event
    void sendInit(int stageNumber, int fragsCount, int lifesCount);
    // Sends moving direction event
    void sendMovingDirectionChanged(QString objectId, AnimatedBoardObject::MovingDirectionType direction);
    // Sends set position and rotation event
    void sendSetPositionAndRotation(QString objectId, int positionX, int positionY, int rotation);
    // Sends control key was pressed event
    void sendControlKeyPressed(QString objectId, int key);
    // Send venet that object fires
    void sendObjectFired(QString objectId);
    // Sends event that object was hit
    void sendHitObject(QString sourceObjectId, QString targetObjectId);
    // Send event that object was created
    void sendObjectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type);
    // Send event that object was removed
    void sendObjectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type);
    // Send event to remove object
    void sendRemoveObject(const QString& objectId);
    // Send event to set moving type
    void sendSetObjectMovingDirectionById(const QString& objectId,
                                      AnimatedBoardObject::MovingDirectionType movingDirection);
    // Send event to create object
    void sendCreateAnimatedObject(AnimatedBoardObject::ObjectType, int,
                                    int, int, AnimatedBoardObject::MovingDirectionType);
    // Send event to add one frag
    void sendAddOneFrag(const QString& userId);
    // Send event to remove one life
    void sendRemoveOneLife(const QString& userId);
    // Setter methods for different properties
    void setGameBoard(GameBoard* board);
    void setGameControllerDelegate(GameControllerProtocol *controller);
    // Returns pointer to game board object
    GameBoard* getGameBoard() const;
    // Called once to initialize
    void initFrame();
    // Called on each interation of game loop
    void nextFrame();

private:
    // The list of AI contexts
    QList<BoardObjectAIContext*> _contexts;
    // The posinter to delegate object which conforms to controller protocol
    GameControllerProtocol *_controllerDelegate;
    // The pointer to game board object
    GameBoard* _board;
};

#endif // STAGEMEDIATOR_H
