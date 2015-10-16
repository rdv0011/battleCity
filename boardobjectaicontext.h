#ifndef BOARDOBJECTAICONTEXT_H
#define BOARDOBJECTAICONTEXT_H

#include <QObject>
#include "animatedboardobject.h"

class BoardObjectAIStrategy;
class StageMediator;
class BoardObjectAIContext : public QObject
{
    Q_OBJECT
public:
    BoardObjectAIContext(QObject *parent, QList<BoardObjectAIStrategy*>, StageMediator*);

    virtual void setMovingDirection(QString objectId, AnimatedBoardObject::MovingDirectionType direction);

    virtual void controlKeyPressed(QString objectId, int key);

    virtual void objectFired(QString objectId);

    virtual void objectHitByObject(QString objectId, QString byObjectId);

    virtual void advance();

    virtual void init();
signals:

public slots:
private:
    QList<BoardObjectAIStrategy*> _strategies;
    StageMediator* _stage;
};

#endif // BOARDOBJECTAICONTEXT_H
