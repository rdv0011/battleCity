#include "tile.h"

Tile::Tile(QObject *parent, int rotation, bool traversible, TileType tileType) :
    BoardObject(parent),
    traversible(traversible),
    tileType(tileType) {
}

const bool Tile::isTraversible() {
    return this->traversible;
}

const Tile::TileType Tile::getTileType() {
    return this->tileType;
}

const QString Tile::getObjectImagePath() {
    QString tileName = "";
    switch (this->tileType) {
    case BRICKWALL:
        tileName = "brickwall";
        break;
    case ARMOREDWALL:
        tileName = "armoredwall";
        break;
    case EMPTY:
    default:
        tileName = "empty_traversable";
        break;
    }
    return "qrc:/images/board/" + tileName + ".png";
}

BoardObject* Tile::constructByCharImpl(QObject *parent, char dataChar, unsigned int position) {
    switch(dataChar) {
    case 'W':
        // Brick wall
        return new Tile(parent, 0, false, BRICKWALL);
        break;
    case 'Z':
        // Armored wall
        return new Tile(parent, 0, false, ARMOREDWALL);
        break;
    case 'X':
        // Blank non traversable space
        return new Tile(parent, 0, false, EMPTY);
        break;
    case 'S':
        // Blank traversible space
        return new Tile(parent, 0, true, EMPTY);
        break;
    default:
        // Return null and give a chance to some other entity to create an instance
        return nullptr;
        break;
    }
}
