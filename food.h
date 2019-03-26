#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>
#include <QColor>

enum FoodType
{
    Simple,
    MakeFaster,
    MakeLower
};

class Food : public QGraphicsItem
{
public:
    Food(const int& foodSize,qreal x, qreal y);
    Food(const int& foodSize,qreal x, qreal y,FoodType foodType,QColor color);


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

    void setFoodType(FoodType foodType);
    FoodType getFoodType();

    void setFoodColor(QColor color);
    QColor getFoodColor();
private:
    const int FOOD_SIZE;
    FoodType foodType;
    QColor foodColor;
};

#endif // FOOD_H
