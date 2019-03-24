#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QString>
#include <QColor>
namespace Ui {
class Settings;
}
struct SettingsData
{
    SettingsData(){}
    SettingsData(int snakeSpeed,int fieldSize,QColor snakeColor,QColor fieldColor)
    {
        this->snakeSpeed = snakeSpeed;
        this->fieldSize = fieldSize;
        this->snakeColor = snakeColor;
        this->fieldColor = fieldColor;
    }
    int snakeSpeed;
    int fieldSize;
    QColor snakeColor;
    QColor fieldColor;
};

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:


    void on_SaveButton_clicked();

    void on_rbCustom_clicked();

    void on_rbExtreme_clicked();

    void on_rbHard_clicked();

    void on_rbMedium_clicked();

    void on_rbEasy_clicked();

    void on_snakeColorBtn_clicked();

    void on_fieldColorBtn_clicked();

signals:
    void sendSettings(SettingsData settings);

private:
    Ui::Settings *ui;
    QColor snakeColor = Qt::yellow;
    QColor fieldColor = Qt::gray;

};

#endif // SETTINGS_H