#include "drops.h"

Drops::Drops(QString n)
{
    name = n;
    counter = 0;
    time = 100;
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Drops::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Drops::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(name == "Sun")
         painter->drawImage(QRectF(-35, -35, 70, 70), QImage(":/images/Interface/Sun.gif"));
    else
    {
        QString image_path = ":/images/Buff/" + name + ".png";
        painter->drawImage(QRectF(-35, -15, 70, 30), QImage(image_path));
    }
}

void Drops::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(name == "Sun")
    {
        Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(270, 955))[0]);
        shop->sun += 25;
    }
    else
    {
        if(name == "Crazy")
        {
            Buff *buff = qgraphicsitem_cast<Buff *>(scene()->items(QPointF(1150, 80))[0]);
            buff->available = 1;
        }
        else if(name == "Ice")
        {
            Buff *buff = qgraphicsitem_cast<Buff *>(scene()->items(QPointF(1150, 140))[0]);
            buff->available = 1;
        }
        else if(name == "Aoe")
        {
            Buff *buff = qgraphicsitem_cast<Buff *>(scene()->items(QPointF(1150, 200))[0]);
            buff->available = 1;
        }
        else if(name == "Fire")
        {
            Buff *buff = qgraphicsitem_cast<Buff *>(scene()->items(QPointF(1150, 320))[0]);
            buff->available = 1;
        }
    }
    counter = time;
    event->setAccepted(true);
}

void Drops::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
        delete this;
}

