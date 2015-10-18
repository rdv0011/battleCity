#ifndef ANIMATEDBOARDOBJECT_H
#define ANIMATEDBOARDOBJECT_H

#include "boardobject.h"

class StageMediator;
// This class contains animated object properties and methods.
// Contains declarations of animated object types, definition of factory method
// to instantinate the object and also contains properties to propagate values to QML objects
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

    // Moving type
    enum MovingDirectionType {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        MOVING_NONE
    };

    // Object constructor
    // rotation: initiail rotation of the animated object
    // type: type of animated object
    // stage: pointer to the stage mediator object
    explicit AnimatedBoardObject(QObject *parent = 0,
                                 int rotation = 0,
                                 ObjectType type = TYPE_NONE,
                                 StageMediator* stage = nullptr);

    // Object destructor
    ~AnimatedBoardObject();

    // Returns path of image file for animated object
    virtual QString getObjectImagePath() const;

    // Stae mediaotr setter
    void setStageMediator(StageMediator*);

    // Type for animated object. To pass
    Q_PROPERTY(ObjectType objectType READ getObjectType CONSTANT)
    // Object type
    ObjectType getObjectType() const;

    // Indicates if animation is paused
    Q_PROPERTY(bool animationPaused READ getAnimationPaused NOTIFY animationPausedChanged)
    // Flag indicates that animation is paused
    bool getAnimationPaused() const;

    // Store moving direction of the object
    Q_PROPERTY(QString movingDirection READ getMovingDirection WRITE setMovingDirection)
    // Moving direction of the object
    void setMovingDirection(QString);
    QString getMovingDirection() const;
    MovingDirectionType getMovingDirectionType() const;

    // Property stores key code to pass it from QML object to C++
    Q_PROPERTY(int controlKeyPressed READ getControlKeyPressed WRITE setControlKeyPressed)
    // Property holds pressed control key value
    int getControlKeyPressed() const;
    void setControlKeyPressed(int);

    // Stores object to be removed. This value passed from QML to C++
    Q_PROPERTY(QString removeObject READ removeObject WRITE setRemoveObject)
    // Object to be removed
    QString removeObject() const;
    void setRemoveObject(QString);


    // Animated object size
    static const int objectWidth = 64;
    static const int objectHeight = 64;
    virtual int getWidth() const;
    virtual int getHeight() const;

    // Setter for object moving type for C++
    void setMovingDirectionType(AnimatedBoardObject::MovingDirectionType movingDirection);

protected:
    // Factory method to construct instance of Tile type
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

signals:
    // Propagate value of animation paused flag to QML
    void animationPausedChanged(bool);

public slots:
private:
    // Animation paused flag
    bool _animationPaused;
    // Object type
    ObjectType _objectType;
    // Moving direction type
    MovingDirectionType _movingDirection;
    // Pointer to stage mediator
    StageMediator* _stage;
};

#endif // ANIMATEDBOARDOBJECT_H
