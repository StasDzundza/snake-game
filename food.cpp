#include <QPainter>

#include "constants.h"
#include "food.h"

Food::Food(const int&foodSize,qreal x, qreal y):FOOD_SIZE(foodSize)
{
    setPos(x, y);
    setData(GD_Type, GO_Food);
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
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}

QPainterPath Food::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(FOOD_SIZE / 2 + 1, FOOD_SIZE / 2 + 1), FOOD_SIZE/2, FOOD_SIZE/2);
    return p;
}
