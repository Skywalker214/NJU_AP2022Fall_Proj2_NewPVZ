#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include "pea.h"

class PeaShooter : public Plant
{
public:
    PeaShooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PEASHOOTER_H
