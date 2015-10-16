#ifndef BOARDOBJECTBUILDERSTRATEGY_H
#define BOARDOBJECTBUILDERSTRATEGY_H

#include <QObject>
#include <QQmlListProperty>
#include <QTextStream>
#include <memory>

class BoardObject;
class BoardObjectBuilderStrategy : public QObject {
    Q_OBJECT
public:
    explicit BoardObjectBuilderStrategy(QObject *parent = 0);

    void setChainOfObjects(BoardObject *chain) {
        chainOfObjects = chain;
    }

    virtual QList<BoardObject*> createStage(QObject *parent, QTextStream& textStream) = 0;
protected:
    BoardObject* chainOfObjects;
};

#endif // BOARDOBJECTBUILDERSTRATEGY_H
