#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include <QColor>
class Wall : public QObject, public QGraphicsItem
{
public:
    Wall (const int& wallSize,qreal x, qreal y,QColor color);
    ~Wall();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    const int WallSize;
    QColor wallColor;
};

#endif // WALL_H
