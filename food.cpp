#include <QPainter>

#include "constants.h"
#include "food.h"

Food::Food(const int&foodSize,qreal x, qreal y):FOOD_SIZE(foodSize)
{
    setPos(x, y);
    setData(GD_Type, GO_Food);
    this->setFoodType(FoodType::Simple);
    this->setFoodColor(Qt::red);
}

Food::Food(const int &foodSize, qreal x, qreal y, FoodType foodType, QColor color):FOOD_SIZE(foodSize)
{
    setPos(x, y);
    setData(GD_Type, GO_Food);
    this->setFoodType(foodType);
    this->setFoodColor(color);
}

QRectF Food::boundingRect() const
{
    return QRectF(-FOOD_SIZE,    -FOOD_SIZE,
                   FOOD_SIZE * 2, FOOD_SIZE * 2 );
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), foodColor);

    painter->restore();
}

QPainterPath Food::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(FOOD_SIZE / 2 + 1, FOOD_SIZE / 2 + 1), FOOD_SIZE/2, FOOD_SIZE/2);
    return p;
}

void Food::setFoodType(FoodType foodType)
{
    this->foodType = foodType;
}

FoodType Food::getFoodType()
{
    return foodType;
}

void Food::setFoodColor(QColor color)
{
    this->foodColor = color;
}

QColor Food::getFoodColor()
{
    return this->foodColor;
}
