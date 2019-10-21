#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <cmath>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

#include "publicspace.h"
#include "block.h"
#include "publicpropertiesdialog.h"

class block;
publicspace::publicspace(){
    func=Park;
    backgroundColor=QColor(201,225,169);
    area=0;
    setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
}

publicspace::publicspace(Function func)
    :func(func){
    if(func==Park)
        backgroundColor=QColor(201,225,169);
    if(func==Square)
        backgroundColor=QColor(210,210,210);
    area=0;
    setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
}

publicspace::~publicspace(){
    nTotalArea-=area;
    if(func==Park){
        nTotalParkArea-=area;
    }
}

int publicspace::getFunction(){
    for(int i=0;i<2;i++){
        if(Function(i)==this->func)
            return i;
    }
    return 0;
}

void publicspace::setFunction(Function func){
    if(this->func!=func){
        this->func=func;
        if(func==Park){
            backgroundColor=QColor(201,225,169);
            nTotalParkArea+=area;
        }
        if(func==Square){
            backgroundColor=QColor(210,210,210);
            nTotalParkArea-=area;
        }
        update();
    }

};

qreal publicspace::getArea(){
    return area;
}

void publicspace::updateArea(){
    area=boundingRect().width()*boundingRect().height();
}

void publicspace::setRect(qreal x, qreal y, qreal width, qreal height){
    if(this->func==Park){
        nTotalArea-=area;
        nTotalParkArea-=area;
        QGraphicsRectItem::setRect(x,y,width,height);
        area=width*height;
        nTotalArea+=area;
        nTotalParkArea+=area;
    }else{
        nTotalArea-=area;
        QGraphicsRectItem::setRect(x,y,width,height);
        area=width*height;
        nTotalArea+=area;
    }
}

void publicspace::setRect(const QRectF & rectangle){
    if(this->func==Park){
        nTotalArea-=area;
        nTotalParkArea-=area;
        QGraphicsRectItem::setRect(rectangle);
        area=rectangle.width()*rectangle.height();
        nTotalArea+=area;
        nTotalParkArea+=area;
    }else{
        nTotalArea-=area;
        QGraphicsRectItem::setRect(rectangle);
        area=rectangle.width()*rectangle.height();
        nTotalArea+=area;
    }
}

void publicspace::mousePressEvent(QGraphicsSceneMouseEvent*event){
    if(event->button()==Qt::LeftButton){
        if(event->modifiers()!=Qt::NoModifier){
            double w=boundingRect().width()/2.0;
            double h=boundingRect().height()/2.0;
            qDebug()<<"Item left clicked with key.";
            QPointF pos=event->scenePos();
            qDebug()<<boundingRect()<<this->pos()<<pos<<event->pos();
            double radius=sqrt(pow(w,2)+pow(h,2));
            double dist=sqrt(pow(this->x()-pos.x(), 2)
                                 + pow(this->y()-pos.y(), 2));
            if(event->modifiers()==Qt::AltModifier||
                    event->modifiers()==Qt::ShiftModifier){
                if(dist/radius>0.6){
                    qDebug()<<dist<<radius<<dist/radius;
                    beResizing=true;
                }else{
                    beResizing=false;
                }
            }else if(event->modifiers()==Qt::ControlModifier){
                if(dist/radius>0.6){
                    qDebug()<<dist<<radius<<dist/radius;
                    rotatable=true;
                    qDebug() << "item right clicked with alt key.";
                    setInitial(event->scenePos());
                }else{
                    rotatable=false;
                }
        }else{
          qDebug() << "Custom item left clicked.";
          setSelected(true);
        }
     }
  }
}

void publicspace::mouseMoveEvent(QGraphicsSceneMouseEvent*event){
    if((event->modifiers()==Qt::AltModifier)&&beResizing){
         QPointF pos=event->scenePos();
         double dist_1=abs(this->x()-pos.x());
         double dist_2=abs(this->y()-pos.y());
         this->setRect(-dist_1,-dist_2,2*dist_1,2*dist_2);
         this->setPos(this->pos());
    }else if((event->modifiers()==Qt::ShiftModifier)&&beResizing){
        nTotalArea-=area;
        if(func==Park){
            nTotalParkArea-=area;
        }
        QPointF pos=event->scenePos();
        double dist_1=abs(this->x()-pos.x());
        this->setScale(dist_1/(boundingRect().width()/2));
        updateArea();
        nTotalArea+=area;
        if(func==Park){
            nTotalParkArea+=area;
        }
    }else if((event->modifiers()==Qt::ControlModifier)&&rotatable){
        QPointF pos=event->scenePos();
        qreal initial_x=initial.x()-this->x();
        qreal initial_y=initial.y()-this->y();
        qreal moved_x=pos.x()-this->x();
        qreal moved_y=pos.y()-this->y();
        qreal angle=(std::atan2(moved_y,moved_x)-
                     std::atan2(initial_y,initial_x))*180.0/3.14;
        this->setRotation(angle);
    }
    else{
        qDebug()<<"item moves.";
        QGraphicsItem::mouseMoveEvent(event);
        qDebug()<<"moved"<<pos();
    }
    //如何做到在这个过程中不进行碰撞检测
//    scene()->collidingItems(this).isEmpty()?
//                setBrush(QBrush(backgroundColor)):
//                setBrush(Qt::red);
}

void publicspace::mouseReleaseEvent(QGraphicsSceneMouseEvent*event){
    if((event->modifiers()==Qt::AltModifier||
        event->modifiers()==Qt::ShiftModifier)&&beResizing){
        beResizing=false;
    }else if((event->modifiers()==Qt::ControlModifier)&&rotatable){
        rotatable=false;
    }else{
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void publicspace::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
    PublicPropertiesDialog Pdialog(this);
    Pdialog.exec();
}

void publicspace::paint(QPainter*painter,
                 const QStyleOptionGraphicsItem*option,
                 QWidget*)
{
    QRectF rect=this->boundingRect();
    QPen pen;
    if(option->state&QStyle::State_Selected){
        pen.setColor(Qt::black);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawRect(rect);
    }
//    if(!scene()->collidingItems(this).isEmpty()){
//        pen.setColor(Qt::red);
//        pen.setWidth(5);
//        painter->setPen(pen);
//        painter->drawRect(rect);
//    }
    //未解决 什么时候进行碰撞检测
    QColor color;
    if(beResizing||rotatable){
        color=backgroundColor;
    }else{
        color=scene()->collidingItems(this).isEmpty()?
                    backgroundColor:Qt::red;
    }
    painter->fillRect(rect,color);
}

int publicspace::type() const{
    return Type;
}

bool publicspace::collidesWithItem(const QGraphicsItem *other,
                                   Qt::ItemSelectionMode)const
{
    QRectF rect=this->boundingRect();
    QPointF topleft=mapToItem(other,rect.topLeft());
    QPointF topright=mapToItem(other,rect.topRight());
    QPointF bottomright=mapToItem(other,rect.bottomRight());
    QPointF bottomleft=mapToItem(other,rect.bottomLeft());
    if(other->type()==UserType+3){
        if(other->contains(topleft)&&other->contains(topright)
                &&other->contains(bottomright)&&other->contains(bottomleft))
            return false;
        else if(!other->contains(topleft)&&!other->contains(topright)
                &&!other->contains(bottomright)&&!other->contains(bottomleft))
            return false;
        else {
            return true;
        }
   }else{
//        return QGraphicsItem::collidesWithItem(other,mode);
        if((other->contains(topleft))||(other->contains(topright))
                ||(other->contains(bottomright))||(other->contains(bottomleft))){
            return true;
        }else{
//           QRectF rect2=other->boundingRect();
//           QPointF topleft2=mapToItem(this,rect2.topLeft());                   ;
//           QPointF topright2=mapToItem(this,rect2.topRight());
//           QPointF bottomright2=mapToItem(this,rect2.bottomRight());
//           QPointF bottomleft2=mapToItem(this,rect2.bottomLeft());
//           if(this->contains(topleft2)||this->contains(topright2)
//                   ||this->contains(bottomright2)||this->contains(bottomleft2)){
//               return true;
//           }else{
               return false;
           }
      }
   }
qreal publicspace::getnTotalArea(){
    return nTotalArea;
}
qreal publicspace::getnTotalParkArea(){
    return nTotalParkArea;
}
qreal publicspace::nTotalArea=0;
qreal publicspace::nTotalParkArea=0;


