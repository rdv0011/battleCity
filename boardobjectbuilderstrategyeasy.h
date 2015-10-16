#ifndef BOARDOBJECTBUILDERSTRATEGYEASY_H
#define BOARDOBJECTBUILDERSTRATEGYEASY_H

#include <boardobjectbuilderstrategy.h>
#include <QQmlListProperty>

class BoardObjectBuilderStrategyEasy : public BoardObjectBuilderStrategy {
    Q_OBJECT
public:
    BoardObjectBuilderStrategyEasy(QObject *parent = 0);

    virtual QList<BoardObject*> createStage(QObject *parent, QTextStream& textStream);
};

#endif // BOARDOBJECTBUILDERSTRATEGYEASY_H
