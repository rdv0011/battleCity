#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#include <QObject>

class BoardObject : public QObject {
    Q_OBJECT
public:
    explicit BoardObject(QObject *parent = 0);

    Q_PROPERTY(QString objectImagePath READ getObjectImagePath CONSTANT)
    // Object's image
    virtual const QString getObjectImagePath();
    void setObjectImagePath(const QString&);

    // Object position
    Q_PROPERTY(int positionX READ getPositionX WRITE setPositionX NOTIFY positionXChanged)
    virtual int getPositionX();
    virtual void setPositionX(int);

    // Object position
    Q_PROPERTY(int positionY READ getPositionY WRITE setPositionY NOTIFY positionYChanged)
    virtual int getPositionY();
    virtual void setPositionY(int);

    Q_PROPERTY(int rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
    // Object's rotation
    virtual int getRotation();
    virtual void setRotation(int);

    void updatePositionAndRotation(int positionX, int positionY, int rotation);

    // Default width
    static const int defaultWidth = 32;
    Q_PROPERTY(int width READ getWidth CONSTANT)
    // Object's width
    virtual const int getWidth();

    // Default height
    static const int defaultHeight = 32;
    Q_PROPERTY(int height READ getHeight CONSTANT)
    // Object's height
    virtual const int getHeight();

    Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
    // Object's visibility
    virtual bool getVisible() const;
    virtual void setVisible(bool);

    void setNext(BoardObject* obj) {
        this->_nextObject = obj;
    }

    // Chain of responsibility. We called next if does not know how to create instance
    virtual BoardObject* constructByChar(QObject *parent, char dataChar, unsigned int position);

    QString getObjectId() const;
    void setObjectId(QString objectId);

signals:
    void positionXChanged(int);
    void positionYChanged(int);
    void rotationChanged(int);
    void visibleChanged(bool);

protected:
    virtual BoardObject* constructByCharImpl(QObject *parent, char dataChar, unsigned int position);

private:
    // Texture for board object
    QString _objectImagePath;
    BoardObject* _nextObject;
    // Object Id
    QString _objectId;
    // Texture rotation in degrees clockwise
    int _rotation;
    int _positionX;
    int _positionY;
    bool _isVisible;
};

#endif // BOARDOBJECT_H
