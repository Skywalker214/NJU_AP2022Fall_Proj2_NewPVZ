#include "pea.h"

Pea::Pea(int a, Zombie *tar, int t)
{
    atk = a;
    target = tar;
    type = t;
    speed = 360.0 * 33 / 1000;

}

QRectF Pea::boundingRect() const
{
    //56*34
    return QRectF(-14, -29, 28, 17);
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(type == 0)
        painter->drawPixmap(QRect(-14, -29, 28, 17), QPixmap(":/images/Plants/Pea/Pea.gif"));
    else if(type == 1)
        painter->drawPixmap(QRect(-14, -29, 28, 17), QPixmap(":/images/Plants/Pea/FirePea.gif"));
}

bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && sqrt(qPow(other->x() - x(), 2) + qPow(other->y() - y(), 2)) < 15;
}

void Pea::advance(int phase)
{
    if (!phase)
        return;
    update();
    if(target == nullptr || target->hp <= 0)
    {
        delete this;
        return;
    }
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        for(int i = 0; i < items.size(); i++)
        {
            if(qgraphicsitem_cast<Zombie *>(items[i]) == target)
            {
                target->hp -= atk;
                if(type == 1)
                {
                    target->onfire = 1;
                    target->onfire_count = 0;
                }
                delete this;
                return;
            }

        }
    }

    qreal sin = (target->y() - y()) / sqrt(qPow((target->x() - x()), 2) + qPow((target->y() - y()), 2));
    qreal cos = (target->x() - x()) / sqrt(qPow((target->x() - x()), 2) + qPow((target->y() - y()), 2));

    qreal dx = speed * cos;
    qreal dy = speed * sin;

    setPos(x() + dx, y() + dy);

}
