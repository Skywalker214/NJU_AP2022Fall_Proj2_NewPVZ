#include "shop.h"

Shop::Shop()
{
    sun = 5000;
    counter = 0;
    time = int(7.0 * 1000 / 33);

    Card *card1 = new Card("PeaShooter");
    card1->setParentItem(this);
    card1->setPos(-157 + 65 * 0, -2);

    Card *card2 = new Card("BonkChoy");
    card2->setParentItem(this);
    card2->setPos(-157 + 65 * 1, -2);

}

QRectF Shop::boundingRect() const
{
    return QRectF(-270, -45, 540, 90);
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/images/Interface/Shop.png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sun));
    painter->drawPoint(-220, 0);
}

void Shop::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (++counter >= time)
    {
        counter = 0;
        sun += 50;
    }
}

void Shop::addPlant(QString s, QPointF pos, int pos_type)
{
    qDebug("addPlant");
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() == Plant::Type)
        {
            qDebug("return 1");
            return;
        }

    if(s == "BonkChoy" && pos_type != 1)
    {
        qDebug("return 2");
        return;
    }
    if(s == "PeaShooter" && pos_type != 0)
    {
        qDebug("return 3");
        return;
    }

    QList<QGraphicsItem *> child = childItems();
    qDebug("%d", child.size());
    foreach (QGraphicsItem *item, child)
    {
        Card *card = qgraphicsitem_cast<Card *>(item);
        if (card->name == s)
        {
            qDebug("find plant type");

            card->counter = 0;
            sun -= card->cost;
            Plant *plant = nullptr;

            if(card->name == "PeaShooter")
            {
                qDebug("place peashooter");
                plant = new PeaShooter();
            }
            else if(card->name == "BonkChoy")
            {
                qDebug("place bonkchoy");
                plant = new BonkChoy();
            }

            plant->setPos(pos);
            scene()->addItem(plant);
        }
    }
    counter = 0;
}
