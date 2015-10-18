#ifndef BOARDOBJECTAISTRATEGY_H
#define BOARDOBJECTAISTRATEGY_H

#include <QObject>
#include "animatedboardobject.h"

class StageMediator;
class GameBoard;
// This class declares base interface for different AI strategies.
class BoardObjectAIStrategy : public QObject {
    Q_OBJECT
public:
    // The increment in pixel for each iteration of game loop
    const int kIncrementStepInPixels = 4;
    // This offset helps to rotate to the left/right even if the object
    // does not reach the corner of the hall of maze. It helps to make navigation easier.
    const int kOffsetToCheck = 16;

    // Constructor
    // stage: pointer to stage mediator
    // game: pointer to game object
    BoardObjectAIStrategy(QObject *parent, StageMediator*, GameBoard*);
    // sets moving direction of the object
    virtual void setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);
    // checks if object hits object object.
    // returns object identifier which input object hits
    // objectid: identifier of the object for which collision should be checked
    // strikingRadius: the radius of actual checking area
    virtual QString getObjectIdHitOther(QString objectId, int strikingRadius);
    // Should be called on each iteration of the game loop
    virtual void advance();

    // Called once to initialize underling stuff
    virtual void init() = 0;
    // Handles control key code for object with identifier
    // objectId: identifier of the object
    // key: key code that was pressed
    virtual void controlKeyPressed(QString objectId, int key) {
        Q_UNUSED(objectId)
        Q_UNUSED(key)
    }
    // Handler for 'fire' event
    // objectId: identifier of the object
    virtual void objectFired(QString objectId) {
        Q_UNUSED(objectId)
    }
    // Handler for 'hit' event
    // objectId: identifier of the object that was hit
    // byObjectId: identifier of the object by which the first object was hit
    virtual void objectHitByObject(QString objectId, QString byObjectId) {
        Q_UNUSED(objectId)
        Q_UNUSED(byObjectId)
    }
    // Handler for event when object was created
    virtual void objectTypeDidCreate(QString objectId, AnimatedBoardObject::ObjectType type) {
        Q_UNUSED(objectId)
        Q_UNUSED(type)
    }
    // Handler for event when object was deleted
    virtual void objectTypeDidRemove(QString objectId, AnimatedBoardObject::ObjectType type) {
        Q_UNUSED(objectId)
        Q_UNUSED(type)
    }
    // Returns moving direction type by rotation angle
    AnimatedBoardObject::MovingDirectionType getMovingDirectionByRotation(int rotation);
    // Returns increment in pixels for moving
    virtual int getObjectStepInPixels() const;

protected:
    // This function changes object's position according to moving direction type
    virtual bool moveToDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);

protected:
    // Pointer to stage mediator
    StageMediator *_stage;
    // pointer to game board object. Using this pointer strategie retrieves postion
    // rotation and other properties of the objects.
    GameBoard* _board;
    unsigned int _gameLoopIterationCount;
};

#endif // BOARDOBJECTAISTRATEGY_H
