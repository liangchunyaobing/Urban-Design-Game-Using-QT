#include <QKeyEvent>
#include <QDebug>
#include "cityscene.h"

QList<QGraphicsItem *> cityscene::collidingItems(const QGraphicsItem *item, Qt::ItemSelectionMode mode) const
{
    Q_D(const QGraphicsScene);//宏通过d_func()获取d指针
    if (!item) {
        qWarning("QGraphicsScene::collidingItems: cannot find collisions for null item");
        return QList<QGraphicsItem *>();
    }

    // Does not support ItemIgnoresTransformations.
    QList<collidingItems *> tmp;
    //获取Scene全部范围的Item
    const auto itemsInVicinity = d->index->estimateItems(item->sceneBoundingRect(), Qt::DescendingOrder);
    for (QGraphicsItem *itemInVicinity : itemsInVicinity) {
    //使用QGraphicsItem的碰撞检测函数测试返回值
        if (item != itemInVicinity && item->collidesWithItem(itemInVicinity, mode))
            tmp << itemInVicinity;
    }
    return tmp;
}
---------------------
作者：allenxguo
来源：CSDN
原文：https://blog.csdn.net/gx864102252/article/details/72625300
版权声明：本文为博主原创文章，转载请附上博文链接！
