#ifndef BOARDOBJECTAISTRATEGY_H
#define BOARDOBJECTAISTRATEGY_H

#include <QObject>
#include "animatedboardobject.h"

class StageMediator;
class BoardObjectAIStrategy : public QObject {
    Q_OBJECT
public:
    const int kIncrementStepInPixels = 4;
    const int kOffsetToCheck = 5;

    BoardObjectAIStrategy(QObject *parent, StageMediator*);

    virtual void setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);

    virtual QString getObjectIdHitOther(QString objectId, int strikingRadius);

    virtual void advance() = 0;

    virtual void init() = 0;

    virtual void controlKeyPressed(QString objectId, int key) {}

    virtual void objectFired(QString objectId) {}

    virtual void objectHitByObject(QString objectId, QString byObjectId) {}

    AnimatedBoardObject::MovingDirectionType getMovingDirectionByRotation(int rotation);

    virtual int getObjectStepInPixels() const;

protected:
    virtual bool moveToDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);

protected:
    StageMediator *_stage;
};

#endif // BOARDOBJECTAISTRATEGY_H
