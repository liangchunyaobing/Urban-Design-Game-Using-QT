#ifndef CITYVIEW_H
#define CITYVIEW_H

#include<QGraphicsView>

class CityView:public QGraphicsView
{
    Q_OBJECT
public:
    CityView(QWidget*parent=NULL);
protected:
    void wheelEvent(QWheelEvent*event);
    //how to drag the scene to move
};

#endif // CITYVIEW_H
