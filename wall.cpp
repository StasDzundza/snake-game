#include "wall.h"
#include "constants.h"
#include <QPainter>
Wall::Wall(const int &wallSize, qreal x, qreal y, QColor color):WallSize(wallSize)
{
    setPos(x, y);
    setData(GD_Type, GO_Wall);
    this->wallColor = color;
}

Wall::~Wall()
{

}

QRectF Wall::boundingRect() const
{
    return QRectF(-WallSize,    -WallSize,
                   WallSize * 2, WallSize * 2 );
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, WallSize, WallSize));
    //foreach (QPointF p, tail) {
    QPointF p(0,5);
    QPointF itemp = mapFromScene(p);
    path.addRect(QRectF(5, 0, WallSize, WallSize));
    //}

    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), wallColor);

    painter->restore();
}
