#ifndef MAP_H
#define MAP_H

#include "other.h"
#include "helper.h"
#include "shop.h"
#include "shovel.h"
#include "buffshop.h"
#include "buffcleaner.h"
#include <QGraphicsSceneDragDropEvent>

class Map: public Other
{
public:
    Map(MapInfo mi);
    //~Map();
    //void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    MapInfo map_info;
};

#endif // MAP_H
