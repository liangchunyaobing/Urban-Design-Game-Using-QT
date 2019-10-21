#ifndef CITYSCENE_H
#define CITYSCENE_H
#include <QGraphicsScene>

class cityscene:public QGraphicsScene
{
protected:
    QList<QGraphicsItem *> collidingItems(const QGraphicsItem *item,
                                          Qt::ItemSelectionMode mode)override;
};

#endif // CITYSCENE_H
