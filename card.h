#ifndef CARD_H
#define CARD_H

#include "other.h"
#include "shop.h"

class Card : public Other
{
public:
    Card(QString n);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    int counter;
    QString name;
    int cost;
    int cool;
};

#endif // CARD_H
