#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDialog>
#include <QString>
#include "settings.h"
#include "food.h"
#include "snake.h"

struct LeaderboardData
{
    LeaderboardData(){}
    LeaderboardData(QString name, QString time ,QString difficult, int fieldSize,int snakeLength)
    {
        this->name = name;this->time = time;this->difficult = difficult;this->fieldSize = fieldSize;this->snakeLength = snakeLength;
    }
    QString name = "";
    QString time = "null";
    QString difficult = "";
    int fieldSize;
    int snakeLength;
};

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(SettingsData settings,QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();

    void snakeAteFood(Food *food);
//    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself();
signals:
    void closeWnd();
public slots:
    void pause();
    void resume();
    void gameOver();

protected:
     bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();
    void AddResultToLeaderboard();

    QTimer timer;
    QGraphicsScene &scene;

    Snake *snake;
    bool isPause;

    SettingsData set;
};

#endif // GAMECONTROLLER_H
