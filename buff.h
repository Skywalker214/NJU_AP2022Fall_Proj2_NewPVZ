#ifndef Buff_H
#define Buff_H

#include "other.h"

class Buff : public Other
{
public:
    Buff(QString n);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    int counter;
    QString name;
    int cool;
    int type;  //1近战 0远程
    int available;
};

#endif // Buff_H
