#ifndef USERBASEAISTRATEGY_H
#define USERBASEAISTRATEGY_H

#include "boardobjectaistrategy.h"

class StageMediator;
class UserBaseAIStrategy : public BoardObjectAIStrategy {
    Q_OBJECT
public:
    UserBaseAIStrategy(QObject* parent, StageMediator* stage);

    virtual void init();

    virtual void advance();

signals:

public slots:
};

#endif // USERBASEAISTRATEGY_H
