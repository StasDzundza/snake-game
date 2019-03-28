#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include <QColor>
class Wall : public QObject, public QGraphicsItem
{
public:
    //enumeration for wall position
    enum Position
    {
        Horizontal,
        Vertical
    };
    Wall (const int& wallSize,const int &wallLength, Position position ,qreal x, qreal y,QColor color);
    ~Wall();

    //Three next functions are virtual,so we should to override them,because class Food derived from QGraphicsItem

    /*This pure virtual function defines the outer bounds of the item as a rectangle; all painting must be restricted
     * to inside an item's bounding rect. QGraphicsView uses this to determine whether the item requires redrawing.*/
    QRectF boundingRect() const;

    /*Returns the shape of this item as a QPainterPath in local coordinates.
         *  The shape is used for many things, including collision detection, hit tests, and for the QGraphicsScene::items() functions.
            In our case,we use it for drawing  the wall object*/
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);//this function draws the wall
private:
    const int WallSize;
    const int WallLength;
    Position position;//vertical or horizontal
    QColor wallColor;
};

#endif // WALL_H
