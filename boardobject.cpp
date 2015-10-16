#include "boardobject.h"
#include "gameboard.h"

BoardObject::BoardObject(QObject *parent) : QObject(parent),
    _rotation(0), _isVisible(true) {
}

const QString BoardObject::getObjectImagePath() {
    return this->_objectImagePath;
}

void BoardObject::setObjectImagePath(const QString& path) {
    this->_objectImagePath = path;
}

int BoardObject::getPositionX() {
    return this->_positionX;
}

void BoardObject::setPositionX(int x) {
    this->_positionX = x;
}

int BoardObject::getPositionY() {
    return this->_positionY;
}

void BoardObject::setPositionY(int y) {
    this->_positionY = y;
}

int BoardObject::getRotation() {
    return this->_rotation;
}

void BoardObject::setRotation(int rotation) {
    this->_rotation = rotation;
}

const int BoardObject::getWidth() {
    return BoardObject::defaultWidth;
}

const int BoardObject::getHeight() {
    return BoardObject::defaultHeight;
}

void BoardObject::setVisible(bool visible) {
    this->_isVisible = visible;
}

bool BoardObject::getVisible() const {
    return this->_isVisible;
}

BoardObject* BoardObject::constructByChar(QObject *parent, char dataChar, unsigned int position) {
    BoardObject* object = constructByCharImpl(parent, dataChar, position);
    if (!object && this->_nextObject) {
        return this->_nextObject->constructByChar(parent, dataChar, position);
    }
    else if (object) {
        GameBoard *board = GameBoard::sharedInstance();
        board->getViewPositionByBoardPostion(position,
                                             object->_positionX,
                                             object->_positionY);
    }
    return object;
}

QString BoardObject::getObjectId() const {
    return this->_objectId;
}

void BoardObject::setObjectId(QString objectId) {
    this->_objectId = objectId;
}

void BoardObject::updatePositionAndRotation(int positionX,
                                            int positionY,
                                            int rotation) {
    this->_positionX = positionX;
    this->_positionY = positionY;
    this->_rotation = rotation;
    emit positionXChanged(positionX);
    emit positionYChanged(positionY);
    emit rotationChanged(rotation);
}

BoardObject* BoardObject::constructByCharImpl(QObject *parent, char dataChar,
                                              unsigned int position) {
    return nullptr;
}
