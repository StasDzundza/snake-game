#include "wall.h"
#include "constants.h"
#include <QPainter>
#include <QDebug>

Wall::Wall(const int &wallSize,const int &wallLength,Position position , qreal x, qreal y, QColor color):WallSize(wallSize),WallLength(wallLength)
{
    setPos(x, y);
    setData(GD_Type, GO_Wall);
    this->wallColor = color;
    this->position = position;
}

Wall::~Wall()
{

}

/*This pure virtual function defines the outer bounds of the item as a rectangle; all painting must be restricted
 * to inside an item's bounding rect. QGraphicsView uses this to determine whether the item requires redrawing.*/
QRectF Wall::boundingRect() const
{
    return QRectF(-WallSize,    -WallSize,
                   WallSize * 2, WallSize * 2 );
}

/*Returns the shape of this item as a QPainterPath in local coordinates.
     *  The shape is used for many things, including collision detection, hit tests, and for the QGraphicsScene::items() functions.
        In our case,we use it for drawing  the wall object*/
QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, WallSize, WallSize));//draw the center of the wall
    int leftToPaint = WallLength - 1;
    int countRectanglesBefore = leftToPaint/2;//calc number of single rectangles before center
    int countRectanglesAfter = leftToPaint - countRectanglesBefore;//calc number of single rectangles after center

    //and there we draw rectangles before center and after center
    if(position == Position::Vertical)
    {
        int deviation = WallLength;//deviation from the center by y coordinate
        for(int i = 0; i < countRectanglesBefore; i++)
        {
            path.addRect(QRectF(0, deviation, WallSize, WallSize));//drawing of the single rectangle
            deviation+=WallLength;//increase deviation to the top
        }
        deviation = -WallLength;
        for(int i = 0; i < countRectanglesAfter; i++)
        {
            path.addRect(QRectF(0, deviation, WallSize, WallSize));//drawing of the single rectangle
            deviation-=WallLength;//decrease deviation to the bottom
        }
    }
    else
    {
        int deviation = WallLength;//deviation from the center by x coordinate
        for(int i = 0; i < countRectanglesBefore; i++)
        {
            path.addRect(QRectF(deviation,0, WallSize, WallSize));//drawing of the single rectangle
            deviation+=WallLength;//increase deviation to the right
        }
        deviation = -WallLength;
        for(int i = 0; i < countRectanglesAfter; i++)
        {
            path.addRect(QRectF(deviation,0, WallSize, WallSize));//drawing of the single rectangle
            deviation-=WallLength;//decrease deviation to the left
        }
    }
    return path;
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)//this function draws the wall
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), wallColor);

    painter->restore();
}
