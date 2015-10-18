#include "animatedboardobject.h"
#include "stagemediator.h"

AnimatedBoardObject::AnimatedBoardObject(QObject *parent,
                                         int rotation,
                                         ObjectType type, StageMediator* stage):BoardObject(parent),
_animationPaused(false), _objectType(type),
  _movingDirection(MOVING_NONE), _stage(stage) {
    setRotation(rotation);
}

AnimatedBoardObject::~AnimatedBoardObject() {

}

int AnimatedBoardObject::getWidth() const {
    return AnimatedBoardObject::objectWidth;
}

int AnimatedBoardObject::getHeight() const {
    return AnimatedBoardObject::objectHeight;
}

AnimatedBoardObject::ObjectType AnimatedBoardObject::getObjectType() const {
    return this->_objectType;
}

QString AnimatedBoardObject::getObjectImagePath() const {
    QString imageName = "";
    switch (this->_objectType) {
    case TYPE_USERBASE:
        imageName = "mybase";
        break;
    case TYPE_ENEMYTANK:
        imageName = "enemytank";
        break;
    case TYPE_USERTANK:
        imageName = "mytank";
        break;
    case TYPE_PROJECTILE:
        imageName = "bullet";
        break;
    case TYPE_EXPLOSION:
        imageName = "explosion";
        break;
    case TYPE_NONE:
        break;
    default:
        imageName = "empty_traversable";
        break;
    }
    return "qrc:/images/" + imageName + ".png";
}

BoardObject* AnimatedBoardObject::constructByCharImpl(QObject *parent, char dataChar,
                                                      unsigned int position) {
    Q_UNUSED(position)

    switch(dataChar) {
    case 'B':
        // User base
        return new AnimatedBoardObject(parent, 0, TYPE_USERBASE);
        break;
    case 'E':
        // Enemy tank
        return new AnimatedBoardObject(parent, 0, TYPE_ENEMYTANK);
        break;
    case 'U':
        // User tank
        return new AnimatedBoardObject(parent, 0, TYPE_USERTANK);
        break;
    default:
        // Return null and give a chance to some other entity to create an instance
        return nullptr;
        break;
    }
}

AnimatedBoardObject::MovingDirectionType AnimatedBoardObject::getMovingDirectionType() const {
    return this->_movingDirection;
}

void AnimatedBoardObject::setMovingDirectionType(AnimatedBoardObject::MovingDirectionType movingDirection) {
    this->_movingDirection = movingDirection;
}

QString AnimatedBoardObject::getMovingDirection() const {
    return "this->_movingDirection";
}

// When user presses key this setter is called
void AnimatedBoardObject::setMovingDirection(QString direction) {
    MovingDirectionType directionToMove = MOVING_NONE;
    if (direction == "Up") {
        directionToMove = MOVING_UP;
    }
    else if (direction == "Down") {
        directionToMove = MOVING_DOWN;
    }
    else if (direction == "Left") {
        directionToMove = MOVING_LEFT;
    }
    else if (direction == "Right") {
        directionToMove = MOVING_RIGHT;
    }
    if (_stage) {
        _stage->sendMovingDirectionChanged(this->getObjectId(), directionToMove);
    }
}


int AnimatedBoardObject::getControlKeyPressed() const {
    return 0;
}

void AnimatedBoardObject::setControlKeyPressed(int controlKey) {
    if (_stage) {
        _stage->sendControlKeyPressed(this->getObjectId(), controlKey);
    }
}

QString AnimatedBoardObject::removeObject() const {
    return "";
}

void AnimatedBoardObject::setRemoveObject(QString objectId) {
    if (_stage) {
        _stage->sendRemoveObject(objectId);
    }
}

bool AnimatedBoardObject::getAnimationPaused() const {
    return this->_animationPaused;
}

void AnimatedBoardObject::setStageMediator(StageMediator* stage) {
    _stage = stage;
}
