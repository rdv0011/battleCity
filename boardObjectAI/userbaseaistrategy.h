#ifndef USERBASEAISTRATEGY_H
#define USERBASEAISTRATEGY_H

#include "boardobjectaistrategy.h"

class StageMediator;
// This class declares interface for concrete strategy to control the user base.
class UserBaseAIStrategy : public BoardObjectAIStrategy {
    Q_OBJECT
public:
    // Constructor
    UserBaseAIStrategy(QObject* parent, StageMediator* stage, GameBoard*);
    // Initialization
    virtual void init();
    // Iteration of game loop
    virtual void advance();
};

#endif // USERBASEAISTRATEGY_H
