#include <gtest/gtest.h>
#include <iostream>
#include "gamecontroller.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "leaderboard.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include<QApplication>
//function which write result to leaderboard(function from class GameController)
bool AddResultToLeaderboard(const char *filename,LeaderboardData& data);

TEST(Snake,Constructor)
{
    SettingsData settings;
    GameController*controller = nullptr;
    Snake*snake = new Snake(5,6,Qt::red,*controller);

    EXPECT_EQ(snake->GetSpeed(),5);
    EXPECT_EQ(snake->GetColor(),Qt::red);

    delete snake;
}

TEST(Snake,Move)
{
    GameController*controller = nullptr;
    Snake*snake = new Snake(5,6,Qt::red,*controller);

    int x = snake->GetHeadXCoordinate();
    int y = snake->GetHeadYCoordinate();

    snake->moveLeft();
    EXPECT_GT(x,snake->GetHeadXCoordinate());
    x = snake->GetHeadXCoordinate();
    y = snake->GetHeadYCoordinate();

    snake->moveRight();
    EXPECT_LT(x,snake->GetHeadXCoordinate());
    x = snake->GetHeadXCoordinate();
    y = snake->GetHeadYCoordinate();

    snake->moveUp();
    EXPECT_GT(y,snake->GetHeadYCoordinate());
    x = snake->GetHeadXCoordinate();
    y = snake->GetHeadYCoordinate();

    snake->moveDown();
    EXPECT_LT(y,snake->GetHeadYCoordinate());

    delete snake;
}

TEST(Snake,advance)
{
    GameController*controller = nullptr;
    Snake*snake = new Snake(5,6,Qt::red,*controller);

    int x = snake->GetHeadXCoordinate();
    int y = snake->GetHeadYCoordinate();

    //check changing of coordinates after advance() function(it depends from the Snake::Direction)
    snake->setMoveDirection(Snake::Direction::MoveLeft);
    EXPECT_GT(x,snake->TestAdvance())<<"Direction is MoveLeft \n";;
    snake->setMoveDirection(Snake::Direction::MoveUp);
    EXPECT_GT(y,snake->TestAdvance())<<"Direction is MoveUp \n";
    snake->setMoveDirection(Snake::Direction::MoveRight);
    EXPECT_LT(x,snake->TestAdvance())<<"Direction is MoveRight \n";;
    snake->setMoveDirection(Snake::Direction::MoveDown);
    EXPECT_LT(y,snake->TestAdvance())<<"Direction is MoveDown. \n";;
    snake->setMoveDirection(Snake::Direction::NoMove);
    EXPECT_EQ(-123,snake->TestAdvance());

    delete snake;
}

TEST(Leaderboard,ReadWrite)
{
    LeaderboardData data;
    data.name = "Stas";
    data.time = "0.00.000";
    data.score = 50;
    data.difficult = "Medium";
    data.fieldSize = 5;

    EXPECT_TRUE(AddResultToLeaderboard("testingWriteRead.txt",data));

    QFile file("testingWriteRead.txt");//opening of file
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))//checks existing of the file
    {
       std::string readName = file.readLine().toStdString();
       std::string readTime = file.readLine().toStdString();
       std::string readDifficult = file.readLine().toStdString();
       std::string readScore = file.readLine().toStdString();
       std::string readFieldSize = file.readLine().toStdString();

       //we compare data with \r\n because convert QByteArray to std::string not correct,but in the snake game everething work nice without \r\n
       EXPECT_EQ("Stas\r\n",readName)<< "Read name incorrect \n";
       EXPECT_EQ("0.00.000\r\n",readTime)<< "Read time incorrect \n";
       EXPECT_EQ("Medium\r\n",readDifficult)<< "Read difficult incorrect \n";
       EXPECT_EQ("50\r\n",readScore)<< "Read score incorrect \n";
       EXPECT_EQ("5\r\n",readFieldSize)<< "Read field size incorrect \n";
    }

}

TEST(Food,SettertGetters)
{
    Food*f = new Food(5,0,0,FoodType::MakeLower,Qt::red);

    EXPECT_EQ(5,f->FOOD_SIZE)<<"Incorrect food size \n";
    EXPECT_EQ(f->foodColor,Qt::red)<<"Incorrect food color \n";
    EXPECT_EQ(FoodType::MakeLower,f->foodType)<<"Incorrect food type \n";

    f->setFoodType(FoodType::MorePointsToScore);
    f->setFoodColor(Qt::green);
    EXPECT_EQ(f->foodColor,Qt::green)<<"Incorrect food color \n";
    EXPECT_EQ(FoodType::MorePointsToScore,f->foodType)<<"Incorrect food type \n";

    delete f;
}

TEST(Stopwatch,time)
{
    stopwatch*st = new stopwatch;
    st->Start();

    QString res;
    QTimer::singleShot(2000,nullptr,[&]{res = st->GetTime();});

    EXPECT_LE(QTime::fromString("00.02.000"),QTime::fromString(res));

    delete st;
}

TEST(Settings,CheckDifficultSettings)
{
    Settings *settings = new Settings;

    settings->on_SaveButton_clicked();

    EXPECT_EQ(6,settings->settings.snakeSpeed);
    EXPECT_EQ(8,settings->settings.fieldSize);
    EXPECT_EQ(settings->snakeColor,Qt::darkMagenta);
    EXPECT_EQ(settings->fieldColor,Qt::gray);
    EXPECT_EQ("Easy",settings->settings.difficult);
    EXPECT_EQ(0,settings->settings.numOfWalls);
    EXPECT_EQ(1,settings->settings.wallLength);
}
int main(int argc,char*argv[])
{
    QApplication a(argc,argv);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

bool AddResultToLeaderboard(const char *filename,LeaderboardData& data)
{
    QFile fileOut(filename); // Связываем объект с файлом fileout.txt
    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream writeStream(&fileOut); // create ne object of QTextStream class
        //write all info into the file
        writeStream << data.name + "\n";
        writeStream << data.time + "\n";
        writeStream << data.difficult + "\n";
        writeStream << QString::number(data.score) + "\n";
        writeStream << QString::number(data.fieldSize) + "\n";
        fileOut.close();//close file
        return true;
    }
    else
    {
        return false;
    }
}
