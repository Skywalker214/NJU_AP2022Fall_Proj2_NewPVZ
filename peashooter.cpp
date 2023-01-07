#include "peashooter.h"

PeaShooter::PeaShooter()
{
    hp = 300;
    atk = 50;
    counter = 0;
    time = int(1.4 * 1000 / 33);
    type_ = 0;

    Aoe = Crazy = Ice = -1;
    Fire = 0;

    range = 600.0;
    setMovie(":/images/Plants/PeaShooter/PeaShooter.gif");
}

void PeaShooter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
    if(Fire)
        painter->drawImage(QRectF(-10, -50, 20, 20), QImage(":/images/Buff/Fire.gif"));
}

void PeaShooter::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;
    else if (++counter >= time)
    {
        counter = 0;
        if (!collidingItems().isEmpty())
        {
            QList<QGraphicsItem *> items = collidingItems();
            if(qgraphicsitem_cast<Zombie *>(items[0])->hp > 0)
            {
                Pea *pea = new Pea(atk, qgraphicsitem_cast<Zombie *>(items[0]), Fire);
                pea->setX(x() + 32);
                pea->setY(y());
                scene()->addItem(pea);
                return;
            }
        }
    }
}

bool PeaShooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && sqrt(qPow(other->x() - x(), 2) + qPow(other->y() - y(), 2)) < range;
}
