#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include "plant.h"
//#include "drops.h"
#include <QtCore/qmath.h>

class Zombie:public QGraphicsItem
{
public:
    enum { Type = UserType + 2};
    Zombie();
    ~Zombie() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);
    void setHead(QString path);

    int hp;
    int sumhp;
    int atk;
    int state;
    qreal speed;
    int dest;
    int speedup;
    int flash;
    int flash_count;
    int onfire;
    int onfire_count;
    int frozen;
    int frozen_count;
    std::vector<std::pair<int, int>> route;

    QMovie *movie;
    QMovie *head;
};



#endif // ZOMBIE_H
