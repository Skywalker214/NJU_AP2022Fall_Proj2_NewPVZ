#ifndef BuffSHOP_H
#define BuffSHOP_H

#include "other.h"
#include "buff.h"
#include "plant.h"

class BuffShop : public Other
{
public:
    BuffShop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    void addBuff(QString s, QPointF pos);
};

#endif // BuffSHOP_H
