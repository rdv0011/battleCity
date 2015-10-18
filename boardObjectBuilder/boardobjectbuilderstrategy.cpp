#include "boardobjectbuilderstrategy.h"

BoardObjectBuilderStrategy::BoardObjectBuilderStrategy(QObject *parent, GameBoard* board) : QObject(parent),
_board(board) {
}
