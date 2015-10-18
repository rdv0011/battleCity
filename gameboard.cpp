#include <QUuid>
#include <QPoint>

#include "gameboard.h"
#include "boardobjectbuilder.h"
#include "boardobjectbuilderstrategyeasy.h"
#include "tile.h"
#include "stagemediator.h"

GameBoard::GameBoard(QObject *parent) : QObject(parent),
 _stage(nullptr), _lifesCount(0), _maximumFragsCount(0) {
}

void GameBoard::init(StageMediator* stage, unsigned int stageNumber) {
    BoardObjectBuilderStrategyEasy strategy(this, this);
    BoardObjectBuilder objectBuilder(this, &strategy, this);
    QList<int> respawnPositions;

    clear();

    _objects = objectBuilder.createStageObjects(this, stageNumber, respawnPositions);
    qDeleteAll(_respawnPoints);
    _respawnPoints.clear();
    for(auto respawnPos : respawnPositions) {
        int positionX, positionY;
        getViewPositionByBoardPostion(respawnPos, positionX, positionY);
        _respawnPoints.append(new QPoint(positionX, positionY));
    }
    _stage = stage;
    _tiles.clear();
    for (auto object : _objects) {
        if (auto animatedObject = dynamic_cast<AnimatedBoardObject*>(object)) {
            animatedObject->setStageMediator(stage);
        }
        if (auto tile = dynamic_cast<Tile*>(object)) {
            _tiles << tile;
        }
    }

    // Lets qml know about changes
    notifyAllAbojectsChanged();
}

void GameBoard::clear() {
    // Wired way to reassign qml objecto to newly created c++ objects
    QList<BoardObject*> tmp(_objects);
    _objects.clear();
    notifyAllAbojectsChanged();
    qDeleteAll(tmp);
    tmp = _frags;
    _frags.clear();
    emit fragsChanged(getFrags());
    qDeleteAll(tmp);
}

GameBoard::~GameBoard() {
    qDeleteAll(_objects);
    _objects.clear();
    qDeleteAll(_frags);
    _frags.clear();
}

int GameBoard::getColsCount() const {
    return GameBoard::colsCount;
}

int GameBoard::getRowsCount() const {
    return GameBoard::rowsCount;
}

QQmlListProperty<Tile> GameBoard::getTiles() {
    QList<Tile*> list;
    for (auto object : _objects) {
        if (auto tile = dynamic_cast<Tile*>(object)) {
            list << tile;
        }
    }
    _tiles = list;
    return QQmlListProperty<Tile>(this, _tiles);
}

QList<AnimatedBoardObject*> GameBoard::getBoardObjectsWithType(AnimatedBoardObject::ObjectType type) const {
    QList<AnimatedBoardObject*> list;
    for (auto object : _objects) {
        if (auto boardObject = dynamic_cast<AnimatedBoardObject*>(object)) {
            if (boardObject->getObjectType() == type || AnimatedBoardObject::TYPE_NONE == type) {
                list << boardObject;
            }
        }
    }
    return list;
}

AnimatedBoardObject* GameBoard::getObjectByObjectId(QString objectId) const {
    AnimatedBoardObject* retObject = nullptr;
    for(auto object : _objects) {
        if (object->getObjectId() == objectId) {
            AnimatedBoardObject* animatedObject =
                    dynamic_cast<AnimatedBoardObject*>(object);
            if (animatedObject) {
                retObject = animatedObject;
                break;
            }
        }
    }
    return retObject;
}

QQmlListProperty<AnimatedBoardObject> GameBoard::getUserBases() {
    _userBases = getBoardObjectsWithType(AnimatedBoardObject::TYPE_USERBASE);
    return QQmlListProperty<AnimatedBoardObject>(this, _userBases);
}

QQmlListProperty<AnimatedBoardObject> GameBoard::getUserTanks() {
    _userTanks = getBoardObjectsWithType(AnimatedBoardObject::TYPE_USERTANK);
    return QQmlListProperty<AnimatedBoardObject>(this, _userTanks);
}

QQmlListProperty<AnimatedBoardObject> GameBoard::getEnemyTanks() {
    _enemyTanks = getBoardObjectsWithType(AnimatedBoardObject::TYPE_ENEMYTANK);
    return QQmlListProperty<AnimatedBoardObject>(this, _enemyTanks);
}

QQmlListProperty<AnimatedBoardObject> GameBoard::getProjectiles() {
    _projectiles = getBoardObjectsWithType(AnimatedBoardObject::TYPE_PROJECTILE);
    return QQmlListProperty<AnimatedBoardObject>(this, _projectiles);
}

QQmlListProperty<AnimatedBoardObject> GameBoard::getExplosions() {
    _explosions = getBoardObjectsWithType(AnimatedBoardObject::TYPE_EXPLOSION);
    return QQmlListProperty<AnimatedBoardObject>(this, _explosions);
}

void GameBoard::getViewPositionByBoardPostion(unsigned int boardPosition,
                                   int& positionX, int& positionY) const {
    int col = boardPosition % getColsCount();
    int row = boardPosition / getColsCount();
    positionX = col * kTileSizeInPixels;
    positionY = row * kTileSizeInPixels;
}

void GameBoard::getObjectPositionAndRotationById(QString objectId, int& positionX,
                                                 int& positionY, int& rotation) const {
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        positionX = object->getPositionX();
        positionY = object->getPositionY();
        rotation = object->getRotation();
    }
}

AnimatedBoardObject::MovingDirectionType GameBoard::getObjectMovingDirectionById(QString objectId) const {
    AnimatedBoardObject::MovingDirectionType movingDirection = AnimatedBoardObject::MOVING_NONE;
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        movingDirection = object->getMovingDirectionType();
    }
    return movingDirection;
}

void GameBoard::setObjectPositionAndRotationById(QString objectId, int positionX,
                                      int positionY, int rotation) {
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        object->updatePositionAndRotation(positionX, positionY, rotation);
    }
}

void GameBoard::setObjectMovingDirectionById(QString objectId,
                                             AnimatedBoardObject::MovingDirectionType movingDirection) {
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        object->setMovingDirectionType(movingDirection);
    }
}


void GameBoard::getObjectSizeById(QString objectId, int& width, int& height) const {
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        width = object->getWidth();
        height = object->getHeight();
    }
}

bool GameBoard::isTileTraversibleWithCoortinates(int positionX, int positionY) const {
    int boardWidth, boardHeight;
    getSizeOfBoardInPixels(boardWidth, boardHeight);
    double kx = (double)positionX / boardWidth;
    double ky = (double)positionY / boardHeight;
    int col = getColsCount() * kx;
    int row = getRowsCount() * ky;
    int tilePosition = row * getColsCount() + col;
    if (tilePosition >= 0 && tilePosition < _tiles.count()) {
        Tile *tile = _tiles[tilePosition];
        if (tile->isTraversible()) {
            return true;
        }
    }
    return false;
}

void GameBoard::getSizeOfBoardInPixels(int& width, int& height) const {
    width = kTileSizeInPixels * getColsCount();
    height = kTileSizeInPixels * getRowsCount();
}

int GameBoard::getTileSize() const {
    return kTileSizeInPixels;
}

void GameBoard::notifyObjectChanged(AnimatedBoardObject::ObjectType type) {
    switch(type) {
    case AnimatedBoardObject::TYPE_USERBASE:
        emit userBasesChanged(getUserBases());
        break;
    case AnimatedBoardObject::TYPE_ENEMYTANK:
        emit enemyTanksChanged(getEnemyTanks());
        break;
    case AnimatedBoardObject::TYPE_USERTANK:
        emit userTanksChanged(getUserTanks());
        break;
    case AnimatedBoardObject::TYPE_PROJECTILE:
        emit projectilesChanged(getProjectiles());
        break;
    case AnimatedBoardObject::TYPE_EXPLOSION:
        emit explosionsChanged(getExplosions());
        break;
    default:
        break;
    }
}

void GameBoard::notifyAllAbojectsChanged() {
    emit userBasesChanged(getUserBases());
    emit enemyTanksChanged(getEnemyTanks());
    emit userTanksChanged(getUserTanks());
    emit projectilesChanged(getProjectiles());
    emit explosionsChanged(getExplosions());
}

QString GameBoard::createAnimatedObject(AnimatedBoardObject::ObjectType type,
                                        int positionX, int positionY, int rotation,
                                        AnimatedBoardObject::MovingDirectionType movingDirection) {
    QString newObjectId;
    if (AnimatedBoardObject::TYPE_NONE != type) {
        AnimatedBoardObject* boardObject = new AnimatedBoardObject(this, rotation, type, _stage);
        newObjectId = QUuid::createUuid().toString();
        boardObject->setObjectId(newObjectId);
        boardObject->setPositionX(positionX);
        boardObject->setPositionY(positionY);
        boardObject->setMovingDirectionType(movingDirection);
        _objects.append(boardObject);
        if (_stage) {
            _stage->sendObjectDidCreate(newObjectId, type);
        }
        notifyObjectChanged(type);
    }
    return newObjectId;
}

void GameBoard::removeObject(QString objectId) {
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        AnimatedBoardObject::ObjectType type = object->getObjectType();
        _objects.removeOne(object);
        if (_stage) {
            _stage->sendObjectDidRemove(objectId, type);
        }
        notifyObjectChanged(type);
        delete object;
    }
}

QList<QString> GameBoard::getObjectIdsByType(AnimatedBoardObject::ObjectType type) const {
    QList<AnimatedBoardObject*> list = getBoardObjectsWithType(type);
    QList<QString> objectIds;
    for(auto object : list) {
        objectIds.append(object->getObjectId());
    }
    return objectIds;
}

AnimatedBoardObject::ObjectType GameBoard::getTypeByObjectId(QString objectId) const {
    AnimatedBoardObject::ObjectType type = AnimatedBoardObject::TYPE_NONE;
    AnimatedBoardObject* object = getObjectByObjectId(objectId);
    if (object) {
        type = object->getObjectType();
    }
    return type;
}

QQmlListProperty<BoardObject> GameBoard::getFrags() {
    return QQmlListProperty<BoardObject>(this, _frags);
}

void GameBoard::createFragObjectsByNumber(unsigned int objectsCount) {
    qDeleteAll(_frags);
    _frags.clear();
    for(unsigned int i = 0; i < objectsCount; i++) {
        BoardObject *fragObject = new BoardObject(this);
        fragObject->setObjectImagePath("qrc:/images/frag_icon.png");
        _frags.append(fragObject);
    }
    _maximumFragsCount = objectsCount;
    emit fragsChanged(getFrags());
    emit fragsCountChanged(getFragsCount());
}

unsigned int GameBoard::getFragsCount() {
    return _maximumFragsCount - _frags.count();
}

unsigned int GameBoard::getMaxFragsCount() {
    return _maximumFragsCount;
}

void GameBoard::addOneFrag(const QString& userId) {

    Q_UNUSED(userId)

    if (_frags.count()) {
        _frags.removeLast();
        emit fragsChanged(getFrags());
        emit fragsCountChanged(getFragsCount());
    }
}

void GameBoard::setLifesCount(unsigned int lifesCount) {
    this->_lifesCount = lifesCount;
    emit lifesCountChanged(_lifesCount);
}

unsigned int GameBoard::getLifesCount() {
    return _lifesCount;
}

void GameBoard::removeOneLife(const QString& userId) {

    Q_UNUSED(userId)

    if (_lifesCount > 0) {
        _lifesCount--;
        emit lifesCountChanged(_lifesCount);
    }
}

QList<QPoint*> GameBoard::getRespawnPointsView() const {
    return _respawnPoints;
}
