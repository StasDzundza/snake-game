#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>

#include "gamecontroller.h"

GameController::GameController(SettingsData settings,QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(settings.snakeSpeed,settings.fieldSize,settings.snakeColor,*this)),
    isPause(false)
{

    timer.start( 1000/33 );
    set = settings;

    Food *a1 = new Food(settings.fieldSize,0, -60);
    scene.addItem(a1);

    scene.addItem(snake);
    //An event filter is an object that
    //receives all events that are sent to this object.
    scene.installEventFilter(this);

    resume();
}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Food *food)
{
    scene.removeItem(food);

    addNewFood();
}

//void GameController::snakeHitWall(Snake *snake, Wall *wall)
//{
//}

void GameController::snakeAteItself()
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    if (!isPause)
        switch (event->key()) {
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
	} while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(set.fieldSize,x, y);
    scene.addItem(food);
}

void GameController::gameOver()
{
    //Этот слот продвигает сцену на один шаг вызывая QGraphicsItem::advance() для всех элементов на сцене.
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        snake = new Snake(set.snakeSpeed,set.fieldSize,set.snakeColor,*this);
        scene.addItem(snake);
        addNewFood();
    } else {
        emit closeWnd();
    }
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
    isPause = true;
}

void GameController::resume()
{
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
