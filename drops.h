#ifndef DROPS_H
#define DROPS_H

#include "other.h"
#include "shop.h"
#include "buff.h"

class Drops : public Other
{
public:
    Drops(QString n);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;

    QString name;
    int counter;
    int time;
};

#endif // DROPS_H
