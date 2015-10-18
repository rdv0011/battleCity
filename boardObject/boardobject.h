#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#include <QObject>

// The base class for building block of the game.
// Contains declarations of object idetifier, position, rotation, size and
// factory method to instantinate the object
class BoardObject : public QObject {
    // Default width in pixels
    const int defaultWidth = 32;
    // Default height in pixels
    const int defaultHeight = 32;

    Q_OBJECT
public:
    // Constructor
    explicit BoardObject(QObject *parent = 0);

    //Object idetifier property
    Q_PROPERTY(QString objectId READ getObjectId CONSTANT)
    // Object id
    virtual QString getObjectId() const;
    virtual void setObjectId(QString objectId);

    // The path to image which associated with the object
    Q_PROPERTY(QString objectImagePath READ getObjectImagePath CONSTANT)
    // Object's image
    virtual QString getObjectImagePath() const;
    virtual void setObjectImagePath(const QString&);

    // Object position x
    Q_PROPERTY(int positionX READ getPositionX WRITE setPositionX NOTIFY positionXChanged)
    virtual int getPositionX() const;
    virtual void setPositionX(int);

    // Object position y
    Q_PROPERTY(int positionY READ getPositionY WRITE setPositionY NOTIFY positionYChanged)
    virtual int getPositionY() const;
    virtual void setPositionY(int);

    // Object's rotation
    Q_PROPERTY(int rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
    virtual int getRotation() const;
    virtual void setRotation(int);

    // Sets position and rotation
    void updatePositionAndRotation(int positionX, int positionY, int rotation);

    // Object's width
    Q_PROPERTY(int width READ getWidth CONSTANT)
    virtual int getWidth() const;

    // Object's height
    Q_PROPERTY(int height READ getHeight CONSTANT)
    virtual int getHeight() const;

    // Set next object in chain to handle the char during instantination
    void setNext(BoardObject* obj) {
        this->_nextObject = obj;
    }

    // Chain of responsibility. We called next if does not know how to create instance
    virtual BoardObject* constructByChar(QObject *parent, char dataChar, unsigned int position);

signals:
    // Signals are sent when corresponding changes should be propagated to QML
    void positionXChanged(int);
    void positionYChanged(int);
    void rotationChanged(int);
    void visibleChanged(bool);

protected:
    // Factory method implementation to instantinate the object in successors
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

private:
    // Image name for object
    QString _objectImagePath;
    // Next objec in chain
    BoardObject* _nextObject;
    // Object Id
    QString _objectId;
    // Iamge rotation in degrees clockwise
    int _rotation;
    int _positionX;
    int _positionY;
    // Stores flag which indicates that object is visible
    bool _isVisible;
};

#endif // BOARDOBJECT_H
