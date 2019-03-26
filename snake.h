#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>
#include "settings.h"
#include <QColor>
class GameController;

class Snake :public QObject, public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(const int&snakeSpeed,const int&snakeSize ,QColor snakeColor,GameController & controller);
    /* Данные методы виртуальные, поэтому их необходимо реализовать
        * в случае наследования от QGraphicsItem
        * */


    /* возвращаем координаты расположения точки
         * по ним будет определяться нажатие точки
         * */

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setMoveDirection(Direction direction);
	Direction currentDirection();

    int GetLength();

    int GetSpeed();
    void SetSpeed(int speed);
protected:
    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

    QPointF        head;
    int            growing;
    int            speed;
    QList<QPointF> tail;
    int            tickCounter;
    Direction      moveDirection;
    GameController &controller;

    const int SNAKE_SIZE;
    QColor SNAKE_COLOR;
};

#endif // SNAKE_H
