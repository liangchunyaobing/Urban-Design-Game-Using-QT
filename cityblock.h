#ifndef CITYBLOCK_H
#define CITYBLOCK_H

#include<QColor>
#include<QGraphicsItem>
#include<QPainterPath>

class QGradient;
class QStyleOptionGraphicsItem;

class cityblock: public QGraphicsItem
{
public:
    enum Kind{Park,Square,BlockPark,TwoBlocks,FourSmallBlocks,LShapedBlock,
              LShapedBlockPlusSmallBlock,BlockPlusTwoSmallBlocks};
    cityblock(Kind kind);
    QRectF boundingRect() const;
    void paint(QPainter*painter,
               const QStyleOptionGraphicsItem*option,QWidget*widget);
private:
    int kind;
    QPainterPath shape;
};

#endif // CITYBLOCK_H
