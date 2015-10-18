#include "boardobjectbuilderstrategyeasy.h"
#include "boardobject.h"
#include "tile.h"
#include "gameboard.h"
#include <QtDebug>

BoardObjectBuilderStrategyEasy::BoardObjectBuilderStrategyEasy(QObject *parent, GameBoard* board):BoardObjectBuilderStrategy(parent, board){
}

QList<BoardObject*> BoardObjectBuilderStrategyEasy::createStageObjects(QObject *parent,
                                                                       QTextStream& textStream,
                                                                       QList<int>& respawnPositions) {
    // Read the data and construct usual/easy level
    // More advanced implementation (strategy hard) might create random objects at higher level of game
    char current;
    QList<BoardObject*> boardObjects;
    if (auto sp = _chainOfObjects) {
        unsigned int position = 0;
        unsigned int objectIdCounter = 0;
        while (!textStream.atEnd()) {
            textStream >> current;
            // ASCII characters are considered only
            if (current > 0x1F) {
                if (current == 'E') {
                    respawnPositions.append(position);
                }
                if (auto object = sp->constructByChar(parent, current, position)) {
                    objectIdCounter++;
                    object->setObjectId(QString("%1").arg(objectIdCounter));
                    int positionX, positionY;
                    _board->getViewPositionByBoardPostion(position,
                                                          positionX,
                                                          positionY);
                    object->setPositionX(positionX);
                    object->setPositionY(positionY);
                    boardObjects << object;
                    // We should create tile under the object
                    // Map file does not contain this tile to keep it readable
                    if (!dynamic_cast<Tile*>(object)) {
                        objectIdCounter++;
                        Tile* tileObject = new Tile(parent, 0, true, Tile::TileType::EMPTY);
                        tileObject->setObjectId(QString("%1").arg(objectIdCounter));
                        int positionX, positionY;
                        _board->getViewPositionByBoardPostion(position,
                                                              positionX,
                                                              positionY);
                        object->setPositionX(positionX);
                        object->setPositionY(positionY);
                        boardObjects << tileObject;
                    }
                }
                else {
                    qDebug().nospace() << qPrintable(QString("Object is unknown for code %1").arg(current));
                }
                position++;
            }
        }
    }
    return boardObjects;
}
