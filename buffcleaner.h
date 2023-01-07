#ifndef BUFFCLEANER_H
#define BUFFCLEANER_H

#include "other.h"
#include "plant.h"

class BuffCleaner : public Other
{
public:
    BuffCleaner();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void removeBuff(QPointF pos);
};

#endif // BUFFCLEANER_H
