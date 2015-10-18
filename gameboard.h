#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QQmlListProperty>

#include "tile.h"
#include "animatedboardobject.h"

class BoardObject;
class StageMediator;
// This class declares interface for game board.
// This is central point for other classes to retrieve
// properties of board objects. Stores board of the game as plain array.
// Contains helper methods for working with board of the game.
class GameBoard : public QObject {

    // The defualt size of tile (smallest part of the game board)
    const int kTileSizeInPixels = 32;
    // Number of columns of tiles on the game board.
    static const int colsCount = 26;
    // Number of rows of tiles on the game board.
    static const int rowsCount = 26;

    Q_OBJECT
public:

    // Constructor
    explicit GameBoard(QObject *parent = 0);

    // Initialization method
    void init(StageMediator* stage, unsigned int);
    // Clears data that is associated with the current stage
    void clear();
    // Destructor
    ~GameBoard();
    // Number of columns of tiles of the game board. Propagated to QML
    Q_PROPERTY(int colsCount READ getColsCount CONSTANT)
    int getColsCount() const;
    // Number of rows of tiles of the game board. Propagated to QML
    Q_PROPERTY(int rowsCount READ getRowsCount CONSTANT)
    int getRowsCount() const;

    // Tiles property. Propagated to QML
    Q_PROPERTY(QQmlListProperty<Tile> tiles READ getTiles NOTIFY tilesChanged)
    QQmlListProperty<Tile> getTiles();
    // The list of user bases. Propagated to QML
    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> userBases READ getUserBases NOTIFY userBasesChanged)
    QQmlListProperty<AnimatedBoardObject> getUserBases();
    // The list of objects that user/users can control. Propagated to QML
    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> userTanks READ getUserTanks NOTIFY userTanksChanged)
    QQmlListProperty<AnimatedBoardObject> getUserTanks();
    // The list of enemy objectsv. Propagated to QML
    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> enemyTanks READ getEnemyTanks NOTIFY enemyTanksChanged)
    QQmlListProperty<AnimatedBoardObject> getEnemyTanks();
    // The list of projectiles. Propagated to QML
    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> projectiles READ getProjectiles NOTIFY projectilesChanged)
    QQmlListProperty<AnimatedBoardObject> getProjectiles();
    // The list of explosions in the game. Propagated to QML
    Q_PROPERTY(QQmlListProperty<AnimatedBoardObject> explosions READ getExplosions NOTIFY explosionsChanged)
    QQmlListProperty<AnimatedBoardObject> getExplosions();
    // Propagated to QML
    Q_PROPERTY(QQmlListProperty<BoardObject> frags READ getFrags NOTIFY fragsChanged)
    QQmlListProperty<BoardObject> getFrags();

    // Frags object. Propagated to QML
    Q_PROPERTY(unsigned int fragsCount READ getFragsCount NOTIFY fragsCountChanged)
    unsigned int getFragsCount();
    void addOneFrag(const QString& userId);
    // Propagated to QML
    Q_PROPERTY(unsigned int maxFragsCount READ getMaxFragsCount NOTIFY maxFragsCountChanged)
    unsigned int getMaxFragsCount();
    // The number of lifes of user. Propagated to QML
    Q_PROPERTY(unsigned int lifesCount READ getLifesCount NOTIFY lifesCountChanged)
    unsigned int getLifesCount();
    void setLifesCount(unsigned int);
    void removeOneLife(const QString& userId);

    // Creates objects for control panel.
    // objectCount: the number of repeated objects
    void createFragObjectsByNumber(unsigned int objectsCount);

    // Returns position in view coordinates by board position(one dimensinal array)
    void getViewPositionByBoardPostion(unsigned int boardPosition, int& positionX, int& positionY) const;

    // Returns all object with whose type is equal to input type
    QList<AnimatedBoardObject*> getBoardObjectsWithType(AnimatedBoardObject::ObjectType type) const;

    // Returns position and rotation of the object by its identifier
    void getObjectPositionAndRotationById(QString objectId, int& positionX,
                                          int& positionY, int& rotation) const;
    // Returns moving direction type by object identifier
    AnimatedBoardObject::MovingDirectionType getObjectMovingDirectionById(QString objectId) const;
    // Set position and rotation of the object by its identifier
    void setObjectPositionAndRotationById(QString objectId, int positionX,
                                          int positionY, int rotation);
    // Set moving direction type by object identifier
    void setObjectMovingDirectionById(QString objectId, AnimatedBoardObject::MovingDirectionType);
    // Returns object width height
    void getObjectSizeById(QString objectId, int& width, int& height) const;
    // Returns if tile is raversible
    bool isTileTraversibleWithCoortinates(int positionX, int positionY) const;
    // Returns the size of the board
    void getSizeOfBoardInPixels(int& width, int& height) const;
    // Return the size of tile
    int getTileSize() const;
    // Factory method to create board object by its type with corresponding position and rotation
    QString createAnimatedObject(AnimatedBoardObject::ObjectType, int positionX,
                                 int positionY, int rotation, AnimatedBoardObject::MovingDirectionType);
    // Removes object from the board array
    void removeObject(QString objectId);
    // Returns object identifiers with corresponding types
    QList<QString> getObjectIdsByType(AnimatedBoardObject::ObjectType) const;
    // Returns the type of object with identifier
    AnimatedBoardObject::ObjectType getTypeByObjectId(QString) const;
    // Returns the list of respawn posint of enemy objects
    QList<QPoint*> getRespawnPointsView() const;

signals:
    // Differents event that called when it is needed to propagate changes to QML objects
    void tilesChanged(QQmlListProperty<Tile>);
    void userBasesChanged(QQmlListProperty<AnimatedBoardObject>);
    void userTanksChanged(QQmlListProperty<AnimatedBoardObject>);
    void enemyTanksChanged(QQmlListProperty<AnimatedBoardObject>);
    void projectilesChanged(QQmlListProperty<AnimatedBoardObject>);
    void explosionsChanged(QQmlListProperty<AnimatedBoardObject>);
    void fragsChanged(QQmlListProperty<BoardObject>);
    void fragsCountChanged(unsigned int);
    void maxFragsCountChanged(unsigned int);
    void lifesCountChanged(unsigned int);

private:
    // Returns object by its identifier. For internal use.
    AnimatedBoardObject* getObjectByObjectId(QString objectId) const;
    // Helper method to propagate changes to QML objects.
    void notifyObjectChanged(AnimatedBoardObject::ObjectType type);
    void notifyAllAbojectsChanged();

private:
    // The game board array. Contains all object of the game including tiles.
    QList<BoardObject*> _objects;
    // The same as above but only for tiles.
    QList<Tile*> _tiles;
    // The same as above but only for user tanks.
    QList<AnimatedBoardObject*> _userTanks;
    // The same as above but only for user bases.
    QList<AnimatedBoardObject*> _userBases;
    // The same as above but only for enemy tanks.
    QList<AnimatedBoardObject*> _enemyTanks;
    // The same as above but only for projectiles.
    QList<AnimatedBoardObject*> _projectiles;
    // The same as above but only for explosions.
    QList<AnimatedBoardObject*> _explosions;
    // The pointer to stage mediator object
    StageMediator* _stage;
    // The frags board object. For QML control panel
    QList<BoardObject*> _frags;
    unsigned int _lifesCount;
    unsigned int _maximumFragsCount;
    // The list of respawn positions of the nemey objects.
    QList<QPoint*> _respawnPoints;
};

#endif // GAMEBOARD_H
