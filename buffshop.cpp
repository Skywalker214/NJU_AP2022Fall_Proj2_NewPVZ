#include "buffshop.h"

BuffShop::BuffShop()
{
    Buff *buff1 = new Buff("Crazy");
    buff1->setParentItem(this);
    buff1->setPos(0, -120);
    Buff *buff2 = new Buff("Ice");
    buff2->setParentItem(this);
    buff2->setPos(0, -60);
    Buff *buff3 = new Buff("Aoe");
    buff3->setParentItem(this);
    buff3->setPos(0, 0);
    Buff *buff4 = new Buff("Fire");
    buff4->setParentItem(this);
    buff4->setPos(0, 120);
}


QRectF BuffShop::boundingRect() const
{
    return QRectF(-50, -150, 100, 300);
}

void BuffShop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void BuffShop::advance(int phase)
{
    if (!phase)
        return;
    update();
}

void BuffShop::addBuff(QString s, QPointF pos)
{
    qDebug("addBuff");
    Plant *plant = nullptr;
    Buff *buff = nullptr;
    for(int i = 0; i < scene()->items(pos).size(); i++)
    {
        if(scene()->items(pos)[i]->type() != Plant::Type)
            continue;
        else
        {
            plant = qgraphicsitem_cast<Plant *>(scene()->items(pos)[i]);
            qDebug("find plant");
        }
    }
    QList<QGraphicsItem *> child = childItems();
    qDebug("%d", child.size());
    foreach (QGraphicsItem *item, child)
    {
        buff = qgraphicsitem_cast<Buff *>(item);
        if (buff->name == s)
        {
            qDebug("find buff type");
            if(buff->type != plant->type_)
            {
                qDebug("wrong buff");
                return;
            }
            else
            {
                if(buff->name == "Fire" && plant->Fire == 0)
                {
                    plant->Fire = 1;
                    buff->counter = 0;
                    qDebug("peashoot get fire");
                }
                if(buff->name == "Crazy" && plant->Crazy == 0 && (plant->Aoe + plant->Ice) < 2)
                {
                    plant->Crazy = 1;
                    qDebug("bonkchoy get crazy");
                    buff->counter = 0;
                }
                if(buff->name == "Aoe" && plant->Aoe == 0 && (plant->Crazy + plant->Ice) < 2)
                {
                    plant->Aoe = 1;
                    qDebug("bonkchoy get aoe");
                    buff->counter = 0;
                }
                if(buff->name == "Ice" && plant->Ice == 0 && (plant->Aoe + plant->Crazy) < 2)
                {
                    plant->Ice = 1;
                    qDebug("bonkchoy get ice");
                    buff->counter = 0;
                }
            }
        }
    }
}

