#include "animatedboardobject.h"
#include "stagemediator.h"

AnimatedBoardObject::AnimatedBoardObject(QObject *parent,
                                         int rotation,
                                         ObjectType type):BoardObject(parent),
_objectType(type), _animationPaused(false), _movingDirection(MOVING_NONE) {
    setRotation(rotation);
}

const int AnimatedBoardObject::getWidth() {
    return AnimatedBoardObject::objectWidth;
}

const int AnimatedBoardObject::getHeight() {
    return AnimatedBoardObject::objectHeight;
}

const AnimatedBoardObject::ObjectType AnimatedBoardObject::getObjectType() {
    return this->_objectType;
}

const QString AnimatedBoardObject::getObjectImagePath() {
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

BoardObject* AnimatedBoardObject::constructByCharImpl(QObject *parent, char dataChar, unsigned int position) {
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

const AnimatedBoardObject::MovingDirectionType AnimatedBoardObject::getMovingDirection() {
    return this->_movingDirection;
}

void AnimatedBoardObject::setMovingDirectionType(AnimatedBoardObject::MovingDirectionType movingDirection) {
    this->_movingDirection = movingDirection;
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

void AnimatedBoardObject::setControlKeyPressed(int controlKey) {
    if (_stage) {
        _stage->sendControlKeyPressed(this->getObjectId(), controlKey);
    }
}

const bool AnimatedBoardObject::getAnimationPaused() {
    return this->_animationPaused;
}

void AnimatedBoardObject::setStageMediator(StageMediator* stage) {
    _stage = stage;
}
