#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>

class Food : public QGraphicsItem
{
public:
    Food(const int& foodSize,qreal x, qreal y);
    /* Данные методы виртуальные, поэтому их необходимо реализовать
        * в случае наследования от QGraphicsItem
        * */


    /* возвращаем координаты расположения точки
         * по ним будет определяться нажатие точки
         * */
    QRectF boundingRect() const;
    //draw the circle on the scene
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
private:
    const int FOOD_SIZE;
};

#endif // FOOD_H
