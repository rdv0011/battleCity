#ifndef TILE_H
#define TILE_H

#include <boardobject.h>

// This class declares interface for small brick of the game board.
// Implements factory method to deserialize tile objects from game data file.
class Tile : public BoardObject {
    Q_OBJECT
public:

    // Tile type
    enum TileType {
        EMPTY,
        BRICKWALL,
        ARMOREDWALL
    };

    // Constructor
    explicit Tile(QObject * = 0,
                  int = 0,
                  bool = false,
                  TileType = EMPTY);
    // Image path
    virtual QString getObjectImagePath() const;

    // Indicates if tile is traversible by animated object
    Q_PROPERTY(bool traversible READ isTraversible CONSTANT)
    // Is traversible
    bool isTraversible() const;

    // Returns type of tile
    Q_PROPERTY(TileType tileType READ getTileType CONSTANT)
    // Tile type
    TileType getTileType() const;

protected:
    // Factory method to construct instance of Tile type
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

private:
    // Indicates the tile is traversible or not
    const bool _traversible;
    // Tile type
    const TileType _tileType;
};

#endif // TILE_H
