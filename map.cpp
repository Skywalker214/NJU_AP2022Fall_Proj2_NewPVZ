#include "map.h"

Map::Map(MapInfo mi)
{
    map_info = mi;
    setAcceptDrops(true);
}

QRectF Map::boundingRect() const
{
    return QRectF(0, 0, 100 * map_info.y, 100 * map_info.x);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
    for(int i = 0; i < map_info.x; i++)
    {
        for(int j = 0; j < map_info.y; j++)
        {
            if(map_info.map[i][j]==0)
                painter->drawPixmap(QRect(100 * j, 100 * i, 100, 100), QPixmap(":/images/Interface/grass0.jpg"));
            else
                painter->drawPixmap(QRect(100 * j, 100 * i, 100, 100), QPixmap(":/images/Interface/grass1.jpg"));
        }
    }
    for(int i = 0; i < (int)map_info.home.size(); i++)
    {
        int tx = map_info.home[i].first;
        int ty = map_info.home[i].second;
        painter->drawPixmap(QRect(100 * ty + 20, 100 * tx + 20, 60, 60), QPixmap(":/images/Interface/brain.png"));
    }
    for(int i = 0; i < (int)map_info.zombie_birthplace.size(); i++)
    {
        int tx = map_info.zombie_birthplace[i].first;
        int ty = map_info.zombie_birthplace[i].second;
        painter->drawPixmap(QRect(100 * ty + 10, 100 * tx, 80, 100), QPixmap(":/images/Interface/Tombstones.png"));
    }
}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->setAccepted(true);
        update();
    }
    else
        event->setAccepted(false);
}

void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    update();
}

void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        QString s = event->mimeData()->text();
        QPointF pos = mapToScene(event->pos());
        qDebug("%f %f", pos.x(), pos.y());
        pos.setX(int(pos.x()) / 100 * 100 + 50);
        pos.setY(int(pos.y()) / 100 * 100 + 50);
        qDebug("%f %f", pos.x(), pos.y());
        if (s == "Shovel")
        {
            Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(600, 960))[0]);
            shovel->removePlant(pos);
        }
        else if(s == "BuffCleaner")
        {
            BuffCleaner *buffcleaner = qgraphicsitem_cast<BuffCleaner *>(scene()->items(QPointF(700, 960))[0]);
            buffcleaner->removeBuff(pos);
        }
        else if(s == "Crazy" || s == "Aoe" || s == "Ice" || s == "Fire")
        {
            BuffShop *buffshop = qgraphicsitem_cast<BuffShop *>(scene()->items(QPointF(1150, 200))[1]);
            buffshop->addBuff(s, pos);
        }
        else
        {
            Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(270, 955))[0]);
            int pos_type = map_info.map[(int)pos.y() / 100][(int)pos.x() / 100];
            qDebug("%d", pos_type);
            shop->addPlant(s, pos, pos_type);
        }
    }
    update();
}
