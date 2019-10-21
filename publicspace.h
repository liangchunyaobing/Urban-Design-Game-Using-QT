#ifndef PUBLICSPACE_H
#define PUBLICSPACE_H

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QColor>

class publicspace:public QGraphicsRectItem
{
    Q_DECLARE_TR_FUNCTIONS(publicspace)
public:
   typedef enum Function{Park,Square}function;
   enum{Type=UserType+1};
   publicspace();
   publicspace(Function func);
   //对象被析构时nTotalrea-=area，
   //如果被析构的对象功能是公园nTotalParkArea-=area
   ~publicspace();
   int getFunction();
   void setFunction(Function func);
   qreal getArea();
   //type（）函数中返回类的Type值，从而在cityscape中实现选中图形的类型判断（函数重载）
   virtual int type() const;
   void setRect(qreal x, qreal y, qreal width, qreal height);
   void setRect(const QRectF & rectangle);
   void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,
              QWidget*);
   static qreal getnTotalArea();
   static qreal getnTotalParkArea();

private:
    Function func;
    QColor backgroundColor;
    bool beResizing;
    bool rotatable;
    QPointF initial;
    qreal area;
    static qreal nTotalArea;
    //static qreal nTotalNumber;
    static qreal nTotalParkArea;
    void setInitial(QPointF initial){this->initial=initial;}
    bool collidesWithItem(const QGraphicsItem *other,
                       Qt::ItemSelectionMode mode=Qt::IntersectsItemShape)const;
    void updateArea();

protected:
   //如果检测到用户按住alt/shift键，判定beResizing是否为真；如果用户没有按键，则选中点击的图形
   void mousePressEvent(QGraphicsSceneMouseEvent*event);
   //shift+鼠标拖动:等比例缩放
   //alt+鼠标拖动:自定义缩放
   //ctrl+鼠标拖动：旋转
   void mouseMoveEvent(QGraphicsSceneMouseEvent*event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent*event);
   //鼠标双击：弹出对象属性框
   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
};

#endif // PUBLICSPACE_H
