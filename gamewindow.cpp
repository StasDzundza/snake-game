#include <QGraphicsView>
#include <QTimer>
#include <qaction.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>

#include "constants.h"
#include "gamecontroller.h"
#include "gamewindow.h"
#include <QIcon>
#include <QStatusBar>

GameWindow::GameWindow(SettingsData settings, QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(settings,*scene, this))
{
    setCentralWidget(view);

    connect(game,SIGNAL(closeWnd()),this,SLOT(close()));
    setFixedSize(800, 800);
    setWindowIcon(QIcon(":/images/snake_ico"));

    createActions();
    createMenus();

    initScene();
    initSceneBackground(settings.fieldSize,settings.fieldColor);

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));

    QStatusBar* bar = new QStatusBar(this);
    this->setStatusBar(bar);
    connect(game,&GameController::sendStatusBarData,this,&GameWindow::UpdateStatusBar);
}
GameWindow::~GameWindow()
{

}

void GameWindow::adjustViewSize()
{
    /*Масштабирует матрицу вида и прокручивает полосы прокрутки чтобы обеспечить
     * что прямоугольник сцены rect помещался в области просмотра.*/
    view->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
}

void GameWindow::createActions()
{
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcuts(QKeySequence::New);
    newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, &QAction::triggered, this, &GameWindow::newGame);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the game"));
    connect(exitAction, &QAction::triggered, this, &GameWindow::close);

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setStatusTip(tr("Pause..."));
    connect(pauseAction, &QAction::triggered, game, &GameController::pause);

    resumeAction = new QAction(tr("&Resume"), this);
    resumeAction->setStatusTip(tr("Resume..."));
    connect(resumeAction, &QAction::triggered, game, &GameController::resume);

    gameHelpAction = new QAction(tr("Game &Help"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("Help on this game"));
    connect(gameHelpAction, &QAction::triggered, this, &GameWindow::gameHelp);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's about box"));
    connect(aboutAction, &QAction::triggered, this, &GameWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void GameWindow::createMenus()
{
    QMenu *options = menuBar()->addMenu(tr("&Options"));
    options->addAction(newGameAction);
    options->addSeparator();
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addSeparator();
    options->addAction(exitAction);

    QMenu *help = menuBar()->addMenu(tr("&Help"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void GameWindow::initScene()
{
    /* Устанавливаем размер сцены по размеру виджета
         * Первая координата - это левый верхний угол,
         * а Вторая - это правый нижний угол
         * */
    scene->setSceneRect(-100, -100, 200, 200);
}

void GameWindow::initSceneBackground(const int& fieldSize,QColor fieldColor)
{

    //заповнюємо сітку(робимо поле)
    QPixmap bg(fieldSize, fieldSize);
    QPainter p(&bg);
    p.setBrush(QBrush(fieldColor));
    p.drawRect(0, 0, fieldSize, fieldSize);

    view->setBackgroundBrush(QBrush(bg));
}

void GameWindow::UpdateStatusBar(QString data)
{
    this->statusBar()->showMessage(data);
}

void GameWindow::newGame()
{
    //запускаємо нову гру
    QTimer::singleShot(0, game, SLOT(gameOver()));

}

void GameWindow::about()
{
    QMessageBox::about(this, tr("About this Game"), tr("<h2>Snake Game</h2>"
        "<p>Copyright &copy; XXX."
        "<p>This game is a small Qt application. It is based on the demo in the GitHub written by Devbean and Stas Dzundza."));
}

void GameWindow::gameHelp()
{
    QMessageBox::about(this, tr("Game Help"), tr("Using direction keys to control the snake to eat the food"
        "<p>Space - pause & resume"));
}

