#include "boardobject.h"

BoardObject::BoardObject(QObject *parent) : QObject(parent),
    _rotation(0), _isVisible(true) {
}

QString BoardObject::getObjectImagePath() const {
    return this->_objectImagePath;
}

void BoardObject::setObjectImagePath(const QString& path) {
    this->_objectImagePath = path;
}

int BoardObject::getPositionX() const {
    return this->_positionX;
}

void BoardObject::setPositionX(int x) {
    this->_positionX = x;
}

int BoardObject::getPositionY() const {
    return this->_positionY;
}

void BoardObject::setPositionY(int y) {
    this->_positionY = y;
}

int BoardObject::getRotation() const {
    return this->_rotation;
}

void BoardObject::setRotation(int rotation) {
    this->_rotation = rotation;
}

int BoardObject::getWidth() const {
    return BoardObject::defaultWidth;
}

int BoardObject::getHeight() const {
    return BoardObject::defaultHeight;
}

BoardObject* BoardObject::constructByChar(QObject *parent, char dataChar, unsigned int position) {
    BoardObject* object = constructByCharImpl(parent, dataChar, position);
    if (!object && this->_nextObject) {
        return this->_nextObject->constructByChar(parent, dataChar, position);
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
    Q_UNUSED(parent)
    Q_UNUSED(dataChar)
    Q_UNUSED(position)
    return nullptr;
}
