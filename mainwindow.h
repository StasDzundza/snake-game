#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include <QPushButton>
#include <QLayout>

class QGraphicsScene;
class QGraphicsView;

class GameController;
class GameWindow;
class Settings;
struct SettingsData;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



private:
    GameWindow*wnd;
    QBoxLayout*layout;
    QPushButton*newGame;
    QPushButton*quit;
    QPushButton*leaderboard;
    QPushButton*settings;

    Settings*settingsWindow;
    SettingsData settingsData;
    void NewGame();
    void CreateButtons();
    void OpenSettings();
    void ShowLeaderBoard();
    void SaveSettings(SettingsData settings);


};

#endif // MAINWINDOW_H
