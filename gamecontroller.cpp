#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QInputDialog>
#include "gamecontroller.h"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTime>

GameController::GameController(SettingsData settings,QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(settings.snakeSpeed,settings.fieldSize,settings.snakeColor,*this)),
    isPause(false)
{
    //seed for random
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    timer.start( 1000/33 );
    set = settings;

    if(set.difficult == "Easy"){pointsForSimpleFood = 1;}
    else if(set.difficult == "Medium"){pointsForSimpleFood = 1;}
    else if(set.difficult == "Hard"){pointsForSimpleFood = 2;}
    else if(set.difficult == "Extreme"){pointsForSimpleFood = 3;}
    else {pointsForSimpleFood = 1;}

    addNewFood();

    addWall();
    addWall();
    addWall();

    scene.addItem(snake);
    //An event filter is an object that
    //receives all events that are sent to this object.
    scene.installEventFilter(this);

    resume();

    connect(&timerForStopwatch,&QTimer::timeout,this,&GameController::SendStopwatchData);
    stopWatch = new stopwatch;

}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Food *food)
{ 
    if(food->getFoodType() == FoodType::MakeFaster)
    {
        int snakeSpeed = snake->GetSpeed();
        if(snakeSpeed/2 == 0){ snake->SetSpeed(snakeSpeed/2 + 1);}
        else{snake->SetSpeed(snakeSpeed/2);}
        connect(&timerForFoodEffect,&QTimer::timeout,[=] { SetDefaultSpeed(snakeSpeed); });
        timerForFoodEffect.start(8000);
    }
    else if(food->getFoodType() == FoodType::MakeLower)
    {
        int snakeSpeed = snake->GetSpeed();
        snake->SetSpeed(snakeSpeed*2);
        connect(&timerForFoodEffect,&QTimer::timeout,[=] { SetDefaultSpeed(snakeSpeed); });
        timerForFoodEffect.start(8000);
    }
    if(food->getFoodType() == FoodType::Simple || food->getFoodType() == FoodType::MakeLower || food->getFoodType() == FoodType::MakeFaster)
    {
        score+=pointsForSimpleFood;
    }
    else
    {
        score+=pointsForMoreScoreFood;
    }
    scene.removeItem(food);

    addNewFood();
}

void GameController::snakeHitWall()
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::snakeAteItself()
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    if (!isPause)
    {
        if(!gameIsStarted && (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right||event->key() == Qt::Key_Up||event->key() == Qt::Key_Down))
        {
            gameIsStarted = true;
            stopWatch->Start();
            timerForStopwatch.start(20);
        }
        switch (event->key())
        {
            case Qt::Key_Left:
                snake->setMoveDirection(Snake::MoveLeft);
                break;
            case Qt::Key_Right:
                snake->setMoveDirection(Snake::MoveRight);
                break;
            case Qt::Key_Up:
                snake->setMoveDirection(Snake::MoveUp);
                break;
            case Qt::Key_Down:
                snake->setMoveDirection(Snake::MoveDown);
                break;
            case Qt::Key_Space:
                pause();
                break;
        }
    }
    else resume();
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int)(qrand() % 200) / 10 - 10;
        y = (int)(qrand() % 200) / 10 - 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));//while is collision between snake and food

    Food *food;

    if(current_step%FoodForSpeedInterval == 0)
    {
        int type = qrand()%2 + 1;
        if(type == 1)
        {
            if(set.fieldColor == Qt::green)
            {
                food = new Food(set.fieldSize,x, y,FoodType::MakeFaster,Qt::cyan);
            }
            else
            {
                food = new Food(set.fieldSize,x, y,FoodType::MakeFaster,Qt::green);
            }
        }
        else
        {
            if(set.fieldColor == Qt::black)
            {
                food = new Food(set.fieldSize,x, y,FoodType::MakeLower,Qt::darkGray);
            }
            else
            {
                food = new Food(set.fieldSize,x, y,FoodType::MakeLower,Qt::black);
            }
        }
    }
    else if(current_step%FoodForPointsInterval == 0)
    {
        if(set.fieldColor == Qt::white)
        {
            food = new Food(set.fieldSize,x, y,FoodType::MorePointsToScore,Qt::darkBlue);
        }
        else
        {
            food = new Food(set.fieldSize,x, y,FoodType::MorePointsToScore,Qt::white);
        }
    }
    else
    {
        if(set.fieldColor == Qt::red)
        {
            food = new Food(set.fieldSize,x, y,FoodType::Simple,Qt::yellow);
        }
        else
        {
            food = new Food(set.fieldSize,x, y,FoodType::Simple,Qt::red);
        }
    }
    current_step++;
    scene.addItem(food);
}

void GameController::addWall()
{
    int x, y;

    do {
        x = (int)(qrand() % 200) / 10 - 10;
        y = (int)(qrand() % 200) / 10 - 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));//while is collision between snake and food

    Wall *wall = new Wall(set.fieldSize,x,y,Qt::green);
    scene.addItem(wall);
}

void GameController::gameOver()
{
    //Этот слот продвигает сцену на один шаг вызывая QGraphicsItem::advance() для всех элементов на сцене.

    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    resultTime = stopWatch->GetTime();
    timerForStopwatch.stop();
    stopWatch->Stop();

    AddResultToLeaderboard();

    score = 0;
    current_step = 1;
    stopWatch->Reset();

    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        snake = new Snake(set.snakeSpeed,set.fieldSize,set.snakeColor,*this);
        scene.addItem(snake);
        addNewFood();
        gameIsStarted = false;
        emit sendStatusBarData("");
    } else {
        emit closeWnd();
    }
}

void GameController::SetDefaultSpeed(int speed)
{
    snake->SetSpeed(speed);
    timerForFoodEffect.stop();
}

void GameController::SendStopwatchData()
{
    emit sendStatusBarData(stopWatch->GetTime() +  "    Score = " + QString::number(score));
}

void GameController::pause()
{
    if(gameIsStarted)
    {
        timerForStopwatch.stop();
        stopWatch->Stop();
    }
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
    isPause = true;
}

void GameController::resume()
{
    if(gameIsStarted)
    {
        stopWatch->Start();
        timerForStopwatch.start(20);
    }
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
    isPause = false;
}
//обробник подій,який буде реагувати на натискання наших клавіш

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    //якщо була натиснута клавіша,то перевіряємо яка
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}

void GameController::AddResultToLeaderboard()
{
    bool bOk;
    QString str = QInputDialog::getText( nullptr, "Input", "Name:", QLineEdit::Normal, "Stas",  &bOk );
    if (!bOk) {
        // Была нажата кнопка Cancel
    }
    else
    {
       LeaderboardData *data = new LeaderboardData;
       data->name = str;
       data->time = resultTime;
       data->difficult = set.difficult;
       data->score = score;
       data->fieldSize = set.fieldSize;

       QFile fileOut("leaderboard.txt"); // Связываем объект с файлом fileout.txt
       if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
       {
           QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
           writeStream << data->name + "\n";
           writeStream << data->time + "\n";
           writeStream << data->difficult + "\n";
           writeStream << QString::number(data->score) + "\n";
           writeStream << QString::number(data->fieldSize) + "\n";
           fileOut.close();
       }

    }
}
