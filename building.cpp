#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <QFontMetricsF>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QLabel>
#include "building.h"
#include "BuildingPropertiesDialog.h"

building::building(){
    func=Residential;
    backgroundColor=QColor(250,225,115);
    text="1F";
    area=0;
    totalArea=0;
    textColor=Qt::black;
    setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
}
building::building(Function func)
    :func(func){
    if(func==Residential)
        backgroundColor=QColor(250,225,115);
    else if(func==Office)
        backgroundColor=QColor(150,210,227);
    else if(func==Cultural)
        backgroundColor=QColor(255,170,170);
    else if(func==Commercial)
        backgroundColor=QColor(255,180,90);
    else if(func==Hotel)
        backgroundColor=QColor(198,183,213);
    else
        backgroundColor=QColor(155,179,202);
    text="1F";
    textColor=Qt::black;
    area=0;
    totalArea=0;
    setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
    }

qreal building::nArea=0;
qreal building::nTotalArea=0;
qreal building::nTotalResArea=0;

//function publicspace::getFunction(){return this->func;}why wrong?
//boundingRect() and paint() using in 构造函数？
building::~building(){
    nArea-=area;
    nTotalArea-=totalArea;
    if(func==Residential){
        nTotalResArea-=totalArea;
    }
}

int building::getFunction(){
    for(int i=0;i<6;i++){
        if(Function(i)==this->func)
            return i;
    }
    return 0;
}

void building::setFunction(Function func){
    if(this->func!=func){
        if(this->func==Residential)
            nTotalResArea-=totalArea;
        this->func=func;
        if(func==Residential){
            backgroundColor=QColor(250,225,115);
            nTotalResArea+=totalArea;
        }
        else if(func==Office)
            backgroundColor=QColor(150,210,227);
        else if(func==Cultural)
            backgroundColor=QColor(255,170,170);
        else if(func==Commercial)
            backgroundColor=QColor(255,180,90);
        else if(func==Hotel)
            backgroundColor=QColor(198,183,213);
        else
            backgroundColor=QColor(155,179,202);
        update();
    }
}
int building::getLayer(){
    return layer;
}
void building::setLayer(int layer){
    if(this->layer!=layer){
        nTotalArea-=totalArea;
        if(func==Residential)
            nTotalResArea-=totalArea;
        this->layer=layer;
        this->text=QString::number(layer)+"F";
        update();
        this->totalArea=area*layer;
        nTotalArea+=totalArea;
        if(func==Residential)
            nTotalResArea+=totalArea;
    }
}

QString building::getText(){
    return text;
}
void building::setText(int layer){
    if(this->layer!=layer){
        nTotalArea-=totalArea;
        if(func==Residential)
            nTotalResArea-=totalArea;
        this->layer=layer;
        this->text=QString::number(layer)+"F";
        update();
        this->totalArea=area*layer;
        nTotalArea+=totalArea;
        if(func==Residential)
            nTotalResArea+=totalArea;
    }
}

qreal building::getTotalArea(){
    return totalArea;
}

void building::updateArea(){
    area=boundingRect().width()*boundingRect().height();
    totalArea=area*layer;
}

QRectF building::outlineRect() const
{
    const int Padding=8;
    QFontMetricsF metrics(qApp->font());
    QRectF rect=metrics.boundingRect(text);
    rect.adjust(-Padding,-Padding,+Padding,+Padding);
    rect.translate(-rect.center());
    return rect;
}

void building::paint(QPainter*painter,
                 const QStyleOptionGraphicsItem*option,
                 QWidget*)
{
    QRectF rect=this->boundingRect();
    if(option->state&QStyle::State_Selected){
        QPen pen(Qt::black);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawRect(rect);
    }
    QColor color=scene()->collidingItems(this).isEmpty()?
                backgroundColor:Qt::red;
    painter->fillRect(rect,color);
    QRectF rect_text=outlineRect();
    painter->setPen(textColor);
    painter->drawText(rect_text,Qt::AlignCenter,text);
}

void building::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    BuildingPropertiesDialog Bdialog(this);
    Bdialog.exec();
}

int building::type()const{
    return Type;
}

qreal building::getnTotalArea(){
    return nTotalArea;
};
qreal building::getnArea(){
    return nArea;
};
qreal building::getnTotalResArea(){
    return nTotalResArea;
};
