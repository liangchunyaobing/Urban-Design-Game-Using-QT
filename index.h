#ifndef INDEX_H
#define INDEX_H

#include "ui_index.h"
#include <QWidget>

class index:public QWidget,private Ui::Index
{
public:
    index(QWidget*parent=nullptr);
    //index(index &i);
private slots:
    void updateIndex();
private:
    qreal siteArea;
    qreal publicArea;
    qreal buildingArea;
    qreal buildingTotalArea;
    qreal parkArea;
    qreal GreenRatio;
    qreal buildingCoverage;
    qreal floorRatio;
};

#endif // INDEX_H
