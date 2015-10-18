#ifndef BOARDOBJECTAICONTEXT_H
#define BOARDOBJECTAICONTEXT_H

#include <QObject>
#include "animatedboardobject.h"

class BoardObjectAIStrategy;
class StageMediator;
// This class is context for different AI strategies.
// Can be configured for different difficulty levels.
class BoardObjectAIContext : public QObject
{
    Q_OBJECT
public:
    // Constructor
    // parent: parent for QObject
    // strategies: The list of AI strategies that this context holds
    // stage: pointer to stage mediator
    BoardObjectAIContext(QObject *parent, QList<BoardObjectAIStrategy*>, StageMediator*);

    // Set moving direction
    // objectId: identifier of the object
    // directio: moving direction of the object
    virtual void setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);
    // Handles control key code for object with identifier
    // objectId: identifier of the object
    // key: key code that was pressed
    virtual void controlKeyPressed(QString objectId, int key);
    // Handler for 'fire' event
    // objectId: identifier of the object
    virtual void objectFired(QString objectId);
    // Handler for 'hit' event
    // objectId: identifier of the object that was hit
    // byObjectId: identifier of the object by which the first object was hit
    virtual void objectHitByObject(QString objectId, QString byObjectId);
    // Handler for event when object was created
    virtual void objectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type);
    // Handler for event when object was deleted
    virtual void objectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type);
    // This fucntion shuld be called from run loop each times on its iteration
    virtual void advance();
    // Called once to initialize underlying stuff
    virtual void init();

private:
    // The list of AI strategies
    QList<BoardObjectAIStrategy*> _strategies;
    // Pointer to stage mediator object
    StageMediator* _stage;
};

#endif // BOARDOBJECTAICONTEXT_H
