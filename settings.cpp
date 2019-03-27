#include "settings.h"
#include "ui_settings.h"
#include <QColorDialog>
#include <cmath>
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->snakeSpeed->setEnabled(false);
    ui->fieldSize->setEnabled(false);
    ui->snakeSpeed->setMaximum(10);
    ui->snakeSpeed->setMinimum(1);
    ui->fieldSize->setMaximum(8);
    ui->fieldSize->setMinimum(3);
    ui->rbEasy->setChecked(true);

    int red = snakeColor.red();
    int green = snakeColor.green();
    int blue = snakeColor.blue();
    ui->snakeColorBtn->setStyleSheet("background-color: rgb(" + QString::number(red) + ',' + QString::number(green) + ',' + QString::number(blue) + ')');

    red = fieldColor.red();
    green = fieldColor.green();
    blue = fieldColor.blue();
    ui->fieldColorBtn->setStyleSheet("background-color: rgb(" + QString::number(red) + ',' + QString::number(green) + ',' + QString::number(blue) + ')');
}

Settings::~Settings()
{
    delete ui;
}

QString Settings::Difficult()
{
    return difficult;
}


void Settings::on_SaveButton_clicked()
{
    if(ui->rbEasy->isChecked())
    {
        settings = SettingsData(6,8,snakeColor,fieldColor,"Easy");
        difficult = "Easy";
        emit sendSettings(settings);
    }
    else if(ui->rbMedium->isChecked())
    {
        settings = SettingsData(4,7,snakeColor,fieldColor,"Medium");
        difficult = "Medium";
        emit sendSettings(settings);
    }
    else if(ui->rbHard->isChecked())
    {
        settings = SettingsData(2,6,snakeColor,fieldColor,"Hard");
        difficult = "Hard";
        emit sendSettings(settings);
    }
    else if(ui->rbExtreme->isChecked())
    {
        settings = SettingsData(1,5,snakeColor,fieldColor,"Extreme");
        difficult = "Extreme";
        emit sendSettings(settings);
    }
    else if(ui->rbCustom->isChecked())
    {
        int speed = abs(ui->snakeSpeed->value() - 10) + 1;
        int size = abs(ui->fieldSize->value()-10) + 1 ;
        settings = SettingsData(speed,size,snakeColor,fieldColor,"Custom");
        difficult = "Custom";
        emit sendSettings(settings);
    }
    close();
}

void Settings::on_rbCustom_clicked()
{
    ui->snakeSpeed->setEnabled(true);
    ui->fieldSize->setEnabled(true);
}

void Settings::on_rbExtreme_clicked()
{

     ui->snakeSpeed->setEnabled(false);
     ui->fieldSize->setEnabled(false);
}

void Settings::on_rbHard_clicked()
{
     ui->snakeSpeed->setEnabled(false);
     ui->fieldSize->setEnabled(false);
}

void Settings::on_rbMedium_clicked()
{
    ui->snakeSpeed->setEnabled(false);
    ui->fieldSize->setEnabled(false);
}

void Settings::on_rbEasy_clicked()
{
    ui->snakeSpeed->setEnabled(false);
    ui->fieldSize->setEnabled(false);
}

void Settings::on_snakeColorBtn_clicked()
{
    QColor color = QColorDialog::getColor();
    snakeColor = color;
    ui->snakeColorBtn->setAutoFillBackground(true);
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    ui->snakeColorBtn->setStyleSheet("background-color: rgb(" + QString::number(red) + ',' + QString::number(green) + ',' + QString::number(blue) + ')');
}

void Settings::on_fieldColorBtn_clicked()
{
    QColor color = QColorDialog::getColor();
    fieldColor = color;
    ui->fieldColorBtn->setAutoFillBackground(true);
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    ui->fieldColorBtn->setStyleSheet("background-color: rgb(" + QString::number(red) + ',' + QString::number(green) + ',' + QString::number(blue) + ')');
}
