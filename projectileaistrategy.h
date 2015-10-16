#ifndef PROJECTILEAISTRATEGY_H
#define PROJECTILEAISTRATEGY_H

#include "boardobjectaistrategy.h"
#include "stagemediator.h"

class ProjectileAIStrategy : public BoardObjectAIStrategy {

    const int kStrikingArea = 8;

    Q_OBJECT
public:
    ProjectileAIStrategy(QObject*, StageMediator*);

    virtual void objectFired(QString objectId);

    virtual void init();

    virtual void advance();

    int getObjectStepInPixels() const;

signals:

public slots:
};

#endif // PROJECTILEAISTRATEGY_H
