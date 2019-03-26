#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDialog>
#include <QString>
#include "settings.h"
#include "food.h"
#include "snake.h"
#include <QTimer>
#include "stopwatch.h"

struct LeaderboardData
{
    LeaderboardData(){}
    LeaderboardData(QString name, QString time ,QString difficult, int fieldSize,int score)
    {
        this->name = name;this->time = time;this->difficult = difficult;this->fieldSize = fieldSize;this->score = score;
    }
    QString name = "";
    QString time = "null";
    QString difficult = "";
    int fieldSize;
    int score;
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
    void sendStatusBarData(QString str);
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
    void SetDefaultSpeed(int speed);
    void SendStopwatchData();
    QTimer timer;
    QGraphicsScene &scene;

    Snake *snake;
    bool isPause;
    bool gameIsStarted = false;

    SettingsData set;

    const int FoodForSpeedInterval = 8;
    const int FoodForPointsInterval = 13;
    int current_step = 1;

    QTimer timerForFoodEffect;

    stopwatch *stopWatch;
    QTimer timePassed;
    QTimer timerForStopwatch;

    int pointsForSimpleFood = 0;
    const int pointsForMoreScoreFood = 20;
    int score = 0;
};

#endif // GAMECONTROLLER_H
