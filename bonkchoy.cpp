#include "bonkchoy.h"

BonkChoy::BonkChoy()
{
    hp = 600;
    atk = 100;
    counter = 0;
    time = int(1.4 * 1000 / 33);
    type_ = 1;

    Aoe = Crazy = Ice = 0;
    Fire = -1;

    range = 30.0;
    setMovie(":/images/Plants/BonkChoy/BonkChoy.gif");
}


QRectF BonkChoy::boundingRect() const
{
    return QRectF(-40, -40, 80, 80);
}


void BonkChoy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(QRectF(-50, -100, 160, 160), movie->currentImage());
    int b_count = 0;
    if(Crazy)
    {
        painter->drawImage(QRectF(-20 + b_count * 20, -50, 20, 20), QImage(":/images/Buff/Crazy.gif"));
        b_count++;
    }
    if(Aoe)
    {
        painter->drawImage(QRectF(-20 + b_count * 20, -50, 20, 20), QImage(":/images/Buff/Aoe.gif"));
        b_count++;
    }
    if(Ice)
    {
        painter->drawImage(QRectF(-20 + b_count * 20, -50, 20, 20), QImage(":/images/Buff/Ice.gif"));
        b_count++;
    }
}


void BonkChoy::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= (time / (Crazy + 1)))
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
            QList<QGraphicsItem *> items = collidingItems();
            if(!Aoe)
            {
                if(qgraphicsitem_cast<Zombie *>(items[0])->hp > 0)
                {
                    qgraphicsitem_cast<Zombie *>(items[0])->hp -= (atk * (Crazy + 1));
                    if(Ice)
                    {
                        qgraphicsitem_cast<Zombie *>(items[0])->frozen = 1;
                        qgraphicsitem_cast<Zombie *>(items[0])->frozen_count = 0;
                    }
                    return;
                }
            }
            else
            {
                for(int i = 0; i < items.size(); i++)
                {
                    if(qgraphicsitem_cast<Zombie *>(items[i])->hp > 0)
                    {
                        qgraphicsitem_cast<Zombie *>(items[i])->hp -= (atk * (Crazy + 1));
                        if(Ice)
                        {
                            qgraphicsitem_cast<Zombie *>(items[i])->frozen = 1;
                            qgraphicsitem_cast<Zombie *>(items[i])->frozen_count = 0;
                        }
                    }
                }
                return;
            }
        }
    }
}


bool BonkChoy::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && sqrt(qPow(other->x() - x(), 2) + qPow(other->y() - y(), 2)) < range;
}
