#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
#include <QGraphicsScene>

#include "block.h"
#include "BlockPropertiesDialog.h"

class QGraphicsScene;

block::block(){
    setFlags(ItemIsSelectable);
    setZValue(-1);
}

block::block(qreal width,qreal height){
    this->width=width;
    this->height=height;
    setFlags(ItemIsSelectable);
    setZValue(-1);
}

void block::setWidth(qreal width){
    prepareGeometryChange();
    this->width=width;
    update();
};

qreal block::getWidth(){
    return width;
};

void block::setHeight(qreal height){
    prepareGeometryChange();
    this->height=height;
    update();
};

qreal block::getHeight(){
    return height;
};

//返回图形的矩形边界（函数重载）
QRectF block::boundingRect() const{
    return QRectF(-width/2,-height/2,width,height);
}

//由矩形边界生成圆角矩形，并返回圆角矩形的边界路径（函数重载）
QPainterPath block::shape() const
{
    QRectF rect=this->boundingRect();
    QPainterPath path;
    path.addRoundRect(rect,10,10);
    return path;
}

//绘制街区：对圆角矩形的边界路径进行颜色填充（函数重载）
void block::paint(QPainter*painter,
                 const QStyleOptionGraphicsItem*option,
                 QWidget*)
{
    if(option->state&QStyle::State_Selected){
        //QRectF rect=this->boundingRect();
        QPen pen(Qt::black);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawPath(this->shape());
     }
    QColor color=scene()->collidingItems(this).isEmpty()?
                QColor(238,238,238):Qt::red;
    painter->fillPath(this->shape(),color);
 }

//鼠标双击：弹出对象属性框
void block::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *){
    BlockPropertiesDialog Bldialog(this);
    Bldialog.exec();
}

//如果检测到用户按住alt/shift键，判定beResizing是否为真；如果用户没有按键，则选中点击的图形
void block::mousePressEvent(QGraphicsSceneMouseEvent*event){
    if(event->button()==Qt::LeftButton){
        if(event->modifiers()==Qt::AltModifier||
                event->modifiers()==Qt::ShiftModifier){
            double w=boundingRect().width()/2.0;
            double h=boundingRect().height()/2.0;
            qDebug()<<"Item left clicked with key.";
            QPointF pos=event->scenePos();
            qDebug()<<boundingRect()<<this->pos()<<pos<<event->pos();
            double radius=sqrt(pow(w,2)+pow(h,2));
            double dist=sqrt(pow(this->x()-pos.x(), 2)
                                 + pow(this->y()-pos.y(), 2));
            if(dist/radius>0.6){
                qDebug()<<dist<<radius<<dist/radius;
                beResizing=true;
            }else{
                beResizing=false;
            }
            }else{
               qDebug() << "Custom item left clicked.";
              setSelected(true);
            }
         }
  }

//shift+鼠标拖动:等比例缩放
//alt+鼠标拖动:自定义缩放
void block::mouseMoveEvent(QGraphicsSceneMouseEvent*event){
    if((event->modifiers()==Qt::AltModifier)&&beResizing){
         QPointF pos=event->scenePos();
         double dist_1=abs(this->x()-pos.x());
         double dist_2=abs(this->y()-pos.y());
         this->setWidth(2*dist_1);
         this->setHeight(2*dist_2);
         this->setPos(this->pos());
    }else if((event->modifiers()==Qt::ShiftModifier)&&beResizing){
        QPointF pos=event->scenePos();
        double dist_1=abs(this->x()-pos.x());
        this->setScale(dist_1/(boundingRect().width()/2));
    }/*else{
        qDebug()<<"item moves.";
        QGraphicsItem::mouseMoveEvent(event);
        qDebug()<<"moved"<<pos();
    }*/
}

void block::mouseReleaseEvent(QGraphicsSceneMouseEvent*event){
    if((event->modifiers()==Qt::AltModifier||
        event->modifiers()==Qt::ShiftModifier)&&beResizing){
        beResizing=false;
    }else{
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

int block::type()const{
    return Type;
}

//检测街区是否与其他街区发生碰撞（函数重载）
bool block::collidesWithItem(const QGraphicsItem *other,
                      Qt::ItemSelectionMode mode)const{
    if(other->type()==UserType+3){
           return QGraphicsItem::collidesWithItem(other,mode);
    }
    else {
            return false;
    }
}
