#include "leaderboard.h"
#include "ui_leaderboard.h"
#include "fstream"
#include <QString>
#include <QDebug>
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
   std::ifstream fin;
   fin.open("leaderboard.bin",std::ios_base::in|std::ios_base::binary);
   if(!fin)
   {
       ui->leaderboard->setText((QString)"Error." + (QString)"\n" + (QString)"Unable open the file \"leaderboard.bin\"!");
   }
   else
   {
       LeaderboardData data;
       while(fin.read((char*)&data,sizeof(LeaderboardData)))
       {
           ui->leaderboard->append("Name : " + data.name + "\n");
           ui->leaderboard->append("Time : " + data.time + "\n");
           ui->leaderboard->append("Snake length : " + QString::number(data.snakeLength) + "\n");
           ui->leaderboard->append("Field size : " + QString::number(data.fieldSize) + "\n");
           ui->leaderboard->append("Difficult : " + data.difficult + "\n");
           ui->leaderboard->append("---------------------------------------------");
       }
   }
   fin.close();
}
