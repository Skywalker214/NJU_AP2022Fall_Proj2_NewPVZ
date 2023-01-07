#ifndef PEA_H
#define PEA_H

#include "other.h"
#include "zombie.h"

class Pea : public Other
{
public:
    Pea(int a, Zombie *tar, int t = 0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;

    int type;
    int atk;
    qreal speed;
    Zombie *target;
};

#endif // PEA_H
