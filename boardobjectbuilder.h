#ifndef BOARDOBJECTBUILDER_H
#define BOARDOBJECTBUILDER_H

#include <QObject>
#include <QQmlListProperty>
#include "boardobjectbuilderstrategy.h"
#include "boardobject.h"

class BoardObjectBuilder : public QObject {
    Q_OBJECT
public:
    BoardObjectBuilder(QObject *parent,
                                BoardObjectBuilderStrategy* strategy);

    void setObjectBuilderStrategy(BoardObjectBuilderStrategy* strategy) {
        builderStrategy = strategy;
    }

    QList<BoardObject*> createStage(QObject *parent, unsigned int stageNumer);

private:
    BoardObjectBuilderStrategy* builderStrategy;
};

#endif // BOARDOBJECTBUILDER_H
