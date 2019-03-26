#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "settings.h"
class QGraphicsScene;
class QGraphicsView;

class GameController;
struct SettingsData;
class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    GameWindow(SettingsData settings, QWidget *parent = 0);
    ~GameWindow();

private slots:
    void adjustViewSize();
    void newGame();
    void gameHelp();
    void about();

private:
    void createActions();
    void createMenus();

    void initScene();
    void initSceneBackground(const int& fieldSize,QColor fieldColor);

    void UpdateStatusBar(QString data);

    QGraphicsScene *scene;
    QGraphicsView *view;

    GameController *game;

    QAction *newGameAction;
    QAction *pauseAction;
    QAction *resumeAction;
    QAction *exitAction;
    QAction *gameHelpAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};

#endif // GAMEWINDOW_H
