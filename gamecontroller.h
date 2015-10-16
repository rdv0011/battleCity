#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class GameBoard;
class StageMediator;
class BoardObjectAIContext;
class GameController : public QObject
{
    Q_OBJECT

    const int kNextFrameTimeout = 30;

public:
    explicit GameController(QObject *parent = 0);

    void initWithStage(unsigned int stageNumber);

    GameBoard* getGameBoard() const;

    void objectWillRemove(QString objectId);

signals:

public slots:
    void nextFrame();

    void aiInit();

private:
    GameBoard* _gameBoard;
    StageMediator* _stage;
    QList<BoardObjectAIContext*> _contexts;
};

#endif // GAMECONTROLLER_H
