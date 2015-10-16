#ifndef ANIMATEDBOARDOBJECT_H
#define ANIMATEDBOARDOBJECT_H

#include "boardobject.h"

class StageMediator;
class AnimatedBoardObject : public BoardObject {
    Q_OBJECT
public:

    // Tile type
    enum ObjectType {
        TYPE_USERBASE,
        TYPE_ENEMYTANK,
        TYPE_USERTANK,
        TYPE_PROJECTILE,
        TYPE_EXPLOSION,
        TYPE_NONE
    };

    enum MovingDirectionType {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        MOVING_NONE
    };

    explicit AnimatedBoardObject(QObject *parent = 0,
                                 int = 0,
                                 ObjectType = TYPE_NONE);

    virtual const QString getObjectImagePath();

    void setStageMediator(StageMediator*);

    Q_PROPERTY(ObjectType objectType READ getObjectType CONSTANT)
    // Object type
    const ObjectType getObjectType();

    Q_PROPERTY(bool animationPaused READ getAnimationPaused NOTIFY animationPausedChanged)
    // Flag indicates that animation is paused
    const bool getAnimationPaused();

    Q_PROPERTY(QString movingDirection WRITE setMovingDirection)
    // Moving direction of the object
    void setMovingDirection(QString);

    const MovingDirectionType getMovingDirection();

    Q_PROPERTY(int controlKeyPressed WRITE setControlKeyPressed)
    // Moving direction of the object
    void setControlKeyPressed(int);


    // Big animated object size
    static const int objectWidth = 64;
    static const int objectHeight = 64;
    virtual const int getWidth();
    virtual const int getHeight();

    void setMovingDirectionType(AnimatedBoardObject::MovingDirectionType movingDirection);

protected:
    // Factory method to construct instance of Tile type
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

signals:
    void animationPausedChanged(bool);

public slots:
private:
    // Animation paused flag
    bool _animationPaused;
    // Object type
    const ObjectType _objectType;
    MovingDirectionType _movingDirection;
    StageMediator* _stage;
};

#endif // ANIMATEDBOARDOBJECT_H
