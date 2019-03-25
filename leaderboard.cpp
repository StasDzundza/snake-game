#include "leaderboard.h"
#include "ui_leaderboard.h"
#include "fstream"
#include <QDebug>
#include <QFile>
using std::string;
Leaderboard::Leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Leaderboard)
{
    ui->setupUi(this);
    ShowLeaderboard();
}

Leaderboard::~Leaderboard()
{
    delete ui;
}

void Leaderboard::ShowLeaderboard()
{
       LeaderboardData data;

       QFile file("leaderboard.txt");
       if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
       {
           while(!file.atEnd())
           {
               ui->leaderboard->append("Name : " + file.readLine() + "\n");
               ui->leaderboard->append("Time : " + file.readLine() + "\n");
               ui->leaderboard->append("Difficult : " + file.readLine() + "\n");
               ui->leaderboard->append("Snake length : " + file.readLine() + "\n");
               ui->leaderboard->append("Field size : " + file.readLine() + "\n");

               ui->leaderboard->append("---------------------------------------------");


           }
       }
       file.close();
}
