#ifndef TANKAISTRATEGY_H
#define TANKAISTRATEGY_H

#include "boardobjectaistrategy.h"
#include "animatedboardobject.h"

class StageMediator;
class TankAIStrategy : public BoardObjectAIStrategy {
    Q_OBJECT
public:
    TankAIStrategy(QObject* parent, StageMediator* stage);

    virtual void controlKeyPressed(QString objectId, int key);

    virtual void objectHitByObject(QString objectId, QString byObjectId);

    virtual void init();

    virtual void advance();

signals:

public slots:
};

#endif // TANKAISTRATEGY_H
