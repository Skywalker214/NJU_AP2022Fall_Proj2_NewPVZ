#ifndef BUTTON_H
#define BUTTON_H

#include "other.h"
#include <QTimer>
#include <QSound>

class Button:public Other
{
public:
    Button(QSound *s, QTimer *t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    QSound *sound;
    QTimer *timer;
};

#endif // BUTTON_H
