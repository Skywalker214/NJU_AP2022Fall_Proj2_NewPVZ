#ifndef BONKCHOY_H
#define BONKCHOY_H

#include "plant.h"

class BonkChoy : public Plant
{
public:
    BonkChoy();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // BONKCHOY_H
