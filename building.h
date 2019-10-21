#ifndef BUILDING_H
#define BUILDING_H

#include "publicspace.h"

class building:public publicspace{
   Q_DECLARE_TR_FUNCTIONS(building)
public:
   typedef enum Function{Residential,Office,Cultural,Hotel,Commercial,Civic}function;
   enum{Type=UserType+2};
   building();
   building(Function func);
   ~building();
   int getFunction();
   void setFunction(Function func);
   int getLayer();
   void setLayer(int layer);
   QString getText();
   void setText(int layer);
   qreal getTotalArea();
   void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,
                    QWidget*);
   virtual int type()const;
   static qreal getnTotalArea();
   static qreal getnArea();
   static qreal getnTotalResArea();
protected:
   //double click to change layer
   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

private:
    Function func;
    int layer;
    qreal area;
    qreal totalArea;
    static qreal nArea;
    static qreal nTotalArea;
    static qreal nTotalResArea;
    //static qreal nTotalOfficeArea;
    QString text;
    QColor textColor;
    QColor backgroundColor;
    QRectF outlineRect() const;
    void updateArea();
};

#endif // BUILDING_H
