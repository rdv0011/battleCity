#ifndef GAMECONTROLLERPROTOCOL
#define GAMECONTROLLERPROTOCOL

#include "animatedboardobject.h"

// Declarees protocol for object create/remove events.
// Implement this interface when you need to be notified of events of objet's life cycle.
class GameControllerProtocol {
public:
    // Handler for object create event
    virtual void objectDidCreate(QString objectId, AnimatedBoardObject::ObjectType type) = 0;
    // Handler for object remove event
    virtual void objectDidRemove(QString objectId, AnimatedBoardObject::ObjectType type) = 0;
};

#endif // GAMECONTROLLERPROTOCOL

