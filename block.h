#ifndef BLOCK_H
#define BLOCK_H

#include<QApplication>
#include<QColor>
#include<QGraphicsItem>
#include<QSet>
#include<QFont>

class block:public QGraphicsItem{
private:
    //街区宽度
    qreal width;
    //街区高度
    qreal height;
    //在MouseMoveEvent函数中用于判定是否进行缩放操作
    bool beResizing;
    //检测街区是否与其他街区发生碰撞（函数重载）
    bool collidesWithItem(const QGraphicsItem *other,
                      Qt::ItemSelectionMode mode=Qt::IntersectsItemShape)const;

public:
    //定义block的Type值
    enum{Type=UserType+3};
    block();
    block(qreal width,qreal height);
    void setWidth(qreal width);
    qreal getWidth();
    void setHeight(qreal height);
    qreal getHeight();
    //type（）函数中返回类的Type值，从而在cityscape中实现选中图形的类型判断（函数重载）
    virtual int type()const;
    //返回图形的矩形边界（函数重载）
    QRectF boundingRect() const;
    //由矩形边界生成圆角矩形，并返回圆角矩形的边界路径（函数重载）
    QPainterPath shape() const;
    //绘制街区：对圆角矩形的边界路径进行颜色填充（函数重载）
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,
                     QWidget*);

protected:
    //如果检测到用户按住alt/shift键，判定beResizing是否为真；如果用户没有按键，则选中点击的图形
    void mousePressEvent(QGraphicsSceneMouseEvent*event);
    //shift+鼠标拖动:等比例缩放
    //alt+鼠标拖动:自定义缩放
    void mouseMoveEvent(QGraphicsSceneMouseEvent*event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*event);
    //鼠标双击：弹出对象属性框
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);   

};

#endif // BLOCK_H
