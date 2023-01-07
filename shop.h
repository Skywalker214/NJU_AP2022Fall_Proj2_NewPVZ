#ifndef SHOP_H
#define SHOP_H

#include "other.h"
#include "card.h"
#include "peashooter.h"
#include "bonkchoy.h"

class Shop : public Other
{
public:
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    void addPlant(QString s, QPointF pos, int pos_type);

    int sun;
    int counter;
    int time;
};

#endif // SHOP_H
