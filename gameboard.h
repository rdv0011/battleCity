#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QQmlListProperty>
#include "tile.h"
#include "animatedboardobject.h"

class BoardObject;
class StageMediator;
class GameBoard : public QObject {
    Q_OBJECT
    const int kTileSizeInPixels = 32;
public:
    static GameBoard* sharedInstance(QObject *parent = 0);

    void init(StageMediator* stage, unsigned int);

    Q_PROPERTY(int colsCount READ getColsCount CONSTANT)
    static int getColsCount();

    // Number of columns of tiles on the game board.
    static const int colsCount = 26;

    Q_PROPERTY(int rowsCount READ getRowsCount CONSTANT)
    static int getRowsCount();

    // Number of rows of tiles on the game board.
    static const int rowsCount = 26;

    Q_PROPERTY(QQmlListProperty<Tile> tiles READ getTiles NOTIFY tilesChanged)
    QQmlListProperty<Tile> getTiles();

    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> userBases READ getUserBases NOTIFY userBasesChanged)
    QQmlListProperty<AnimatedBoardObject> getUserBases();

    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> userTanks READ getUserTanks NOTIFY userTanksChanged)
    QQmlListProperty<AnimatedBoardObject> getUserTanks();

    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> enemyTanks READ getEnemyTanks NOTIFY enemyTanksChanged)
    QQmlListProperty<AnimatedBoardObject> getEnemyTanks();

    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> projectiles READ getProjectiles NOTIFY projectilesChanged)
    QQmlListProperty<AnimatedBoardObject> getProjectiles();

    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> explosions READ getExplosions NOTIFY explosionsChanged)
    QQmlListProperty<AnimatedBoardObject> getExplosions();

    Q_PROPERTY(QQmlListProperty<BoardObject> frags READ getFrags NOTIFY fragsChanged)
    QQmlListProperty<BoardObject> getFrags();

    void createFragObjectsByNumber(unsigned int objectsCount);

    Q_PROPERTY(unsigned int fragsCount READ getFragsCount NOTIFY fragsCountChanged)
    unsigned int getFragsCount();
    void removeOneFrag();

    Q_PROPERTY(unsigned int maxFragsCount READ getMaxFragsCount NOTIFY maxFragsCountChanged)
    unsigned int getMaxFragsCount();

    Q_PROPERTY(unsigned int flagsCount READ getFlagsCount NOTIFY flagsCountChanged)
    unsigned int getFlagsCount();
    void addOneFlag();

    void getViewPositionByBoardPostion(unsigned int boardPosition, int& positionX, int& positionY) const;

    QList<AnimatedBoardObject*> getBoardObjectsWithType(AnimatedBoardObject::ObjectType type) const;

    void getObjectPositionAndRotationById(QString objectId, int& positionX,
                                          int& positionY, int& rotation) const;
    AnimatedBoardObject::MovingDirectionType getObjectMovingDirectionById(QString objectId) const;

    void setObjectPositionAndRotationById(QString objectId, int positionX,
                                          int positionY, int rotation);

    void setObjectMovingDirectionById(QString objectId, AnimatedBoardObject::MovingDirectionType);

    void getObjectSizeById(QString objectId, int& width, int& height) const;

    bool isTileTraversibleWithCoortinates(int positionX, int positionY) const;

    void getSizeOfBoardInPixels(int& width, int& height) const;

    int getTileSize() const;

    QString createAnimatedObject(AnimatedBoardObject::ObjectType, int positionX,
                                 int positionY, int rotation, AnimatedBoardObject::MovingDirectionType);

    void removeObject(QString objectId);

    QList<QString> getObjectIdsByType(AnimatedBoardObject::ObjectType) const;

    AnimatedBoardObject::ObjectType getTypeByObjectId(QString) const;

    void setObjectVisible(QString objectId, bool);


signals:
    void tilesChanged(QQmlListProperty<Tile>);
    void userBasesChanged(QQmlListProperty<AnimatedBoardObject>);
    void userTanksChanged(QQmlListProperty<AnimatedBoardObject>);
    void enemyTanksChanged(QQmlListProperty<AnimatedBoardObject>);
    void projectilesChanged(QQmlListProperty<AnimatedBoardObject>);
    void explosionsChanged(QQmlListProperty<AnimatedBoardObject>);
    void fragsChanged(QQmlListProperty<BoardObject>);
    void fragsCountChanged(unsigned int);
    void maxFragsCountChanged(unsigned int);
    void flagsCountChanged(unsigned int);

private:
    explicit GameBoard(QObject *parent = 0);
    AnimatedBoardObject* getObjectByObjectId(QString objectId) const;
    void notifyObjectChanged(AnimatedBoardObject::ObjectType type);

private:
    QList<BoardObject*> _objects;
    QList<Tile*> _tiles;
    QList<AnimatedBoardObject*> _userTanks;
    QList<AnimatedBoardObject*> _userBases;
    QList<AnimatedBoardObject*> _enemyTanks;
    QList<AnimatedBoardObject*> _projectiles;
    QList<AnimatedBoardObject*> _explosions;
    StageMediator* _stage;
    QList<BoardObject*> _frags;
    unsigned int _flagsCount;
    unsigned int _maximumFragsCount;
};

#endif // GAMEBOARD_H
