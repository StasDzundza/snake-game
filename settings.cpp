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


void Settings::on_SaveButton_clicked()
{
    if(ui->rbEasy->isChecked())
    {
        SettingsData data(6,7,snakeColor,fieldColor);
        emit sendSettings(data);
    }
    else if(ui->rbMedium->isChecked())
    {
        SettingsData data(5,6,snakeColor,fieldColor);
        emit sendSettings(data);
    }
    else if(ui->rbHard->isChecked())
    {
        SettingsData data(2,4,snakeColor,fieldColor);
        emit sendSettings(data);
    }
    else if(ui->rbExtreme->isChecked())
    {
        SettingsData data(1,4,snakeColor,fieldColor);
        emit sendSettings(data);
    }
    else if(ui->rbCustom->isChecked())
    {
        int speed = abs(ui->snakeSpeed->value() - 10) + 1;
        int size = abs(ui->fieldSize->value()-10) + 1 ;
        SettingsData data(speed,size,snakeColor,fieldColor);
        emit sendSettings(data);
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
