#ifndef TILE_H
#define TILE_H

#include <boardobject.h>

class Tile : public BoardObject {
    Q_OBJECT
public:

    // Tile type
    enum TileType {
        EMPTY,
        BRICKWALL,
        ARMOREDWALL
    };

    explicit Tile(QObject * = 0,
                  int = 0,
                  bool = false,
                  TileType = EMPTY);

    virtual const QString getObjectImagePath();

    Q_PROPERTY(bool traversible READ isTraversible CONSTANT)
    // Is traversible
    const bool isTraversible();

    Q_PROPERTY(TileType tileType READ getTileType CONSTANT)
    // Tile type
    const TileType getTileType();

protected:
    // Factory method to construct instance of Tile type
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

private:
    // Indicates the tile is traversible or not
    const bool traversible;
    // Tile type
    const TileType tileType;
};

#endif // TILE_H
