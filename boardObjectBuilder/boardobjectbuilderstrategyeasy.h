#ifndef BOARDOBJECTBUILDERSTRATEGYEASY_H
#define BOARDOBJECTBUILDERSTRATEGYEASY_H

#include <boardobjectbuilderstrategy.h>
#include <QQmlListProperty>

// This class declares interface for concrete building strategy of stage
class BoardObjectBuilderStrategyEasy : public BoardObjectBuilderStrategy {
    Q_OBJECT
public:
    // Constructor
    BoardObjectBuilderStrategyEasy(QObject *parent, GameBoard* board);
    // Returns game board objects
    // respawnPoints: the list of respaw points of enemies
    virtual QList<BoardObject*> createStageObjects(QObject *parent,
                                                   QTextStream& textStream,
                                                   QList<int>& respawnPositions);
};

#endif // BOARDOBJECTBUILDERSTRATEGYEASY_H
