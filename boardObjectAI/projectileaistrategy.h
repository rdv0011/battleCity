#ifndef PROJECTILEAISTRATEGY_H
#define PROJECTILEAISTRATEGY_H

#include "boardobjectaistrategy.h"
#include "stagemediator.h"

// This class declares interface of concrete strategy to control projectile
class ProjectileAIStrategy : public BoardObjectAIStrategy {

    // The striking area of the projectile
    const int kStrikingArea = 8;

    Q_OBJECT
public:

    // Constructor
    ProjectileAIStrategy(QObject*, StageMediator*, GameBoard*);
    // Called when object fired
    virtual void objectFired(QString objectId);
    // Initialize underling stuff
    virtual void init();
    // Called on each iteration of the game loop
    virtual void advance();
    // Returns step of object movement on each iteration of the game loop
    int getObjectStepInPixels() const;
};

#endif // PROJECTILEAISTRATEGY_H
