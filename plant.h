#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "zombie.h"
#include <QtCore/qmath.h>

class Plant: public QGraphicsItem
{
public:
    enum { Type = UserType + 1};
    Plant();
    ~Plant() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);

    int hp;
    int atk;
    int counter;
    int time;
    int type_;

    int Aoe;
    int Crazy;
    int Ice;
    int Fire;

    qreal range;

    QMovie *movie;
};

#endif // PLANT_H
