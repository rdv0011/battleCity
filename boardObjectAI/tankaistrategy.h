#ifndef TANKAISTRATEGY_H
#define TANKAISTRATEGY_H

#include "boardobjectaistrategy.h"
#include "animatedboardobject.h"

class QSound;
class QTimer;
class StageMediator;
// This class declares interface of concrete strategy to control tank
class TankAIStrategy : public BoardObjectAIStrategy {
    // File names of different sounds for this strategy
    const QString kShotSoundFileName = ":/sounds/shot.wav";
    const QString kExplosionFileName = ":/sounds/explosion.wav";
    const QString kUserMovingFileName = ":/sounds/userMoving.wav";
    const int kFiringSpeedFactor = 10;

    Q_OBJECT
public:
    // Constructor
    TankAIStrategy(QObject* parent, StageMediator* stage, GameBoard*);
    // Control key pressed by user
    virtual void controlKeyPressed(QString objectId, int key);
    // Handler of event when one object hit another
    virtual void objectHitByObject(QString objectId, QString byObjectId);
    // Handler of event when object with conrcrete type was created
    virtual void objectTypeDidCreate(QString objectId, AnimatedBoardObject::ObjectType type);
    // Handler of event when object with conrcrete type was deleted
    virtual void objectTypeDidRemove(QString objectId, AnimatedBoardObject::ObjectType type);
    // Initialization
    virtual void init();
    // Called on each iteration of game loop
    virtual void advance();

public slots:
    // Fires when moving sounds should be stopped
    void stopUserMovingSound();

private:
    // Stores identifiers of enemy projectiles
    QList<QString> _enemyProjectiles;
    // Stores type of object that fired the last
    AnimatedBoardObject::ObjectType _lastFiredObject;
    // Object to play moving sound
    QSound* _userMovingSound;
    QTimer* _userMovingSoundTimer;
    bool _isUserTankFiring;
};

#endif // TANKAISTRATEGY_H
