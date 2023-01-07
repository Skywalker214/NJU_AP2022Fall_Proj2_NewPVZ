#include "buffcleaner.h"

BuffCleaner::BuffCleaner()
{

}

QRectF BuffCleaner::boundingRect() const
{
    return QRectF(-40, -40, 80, 80);
}

void BuffCleaner::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-40, -40, 80, 80), QPixmap(":/images/Interface/ShovelBank.png"));
    painter->drawPixmap(QRect(-35, -35, 70, 70), QPixmap(":/images/Interface/BuffCleaner.png"));
}

void BuffCleaner::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void BuffCleaner::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length()
            < QApplication::startDragDistance())
        return;
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/images/Interface/BuffCleaner.png");
    mime->setText("BuffCleaner");
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image).scaled(70, 70));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void BuffCleaner::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}

void BuffCleaner::removeBuff(QPointF pos)
{
    QList<QGraphicsItem *> items = scene()->items(pos);
    foreach (QGraphicsItem *item, items)
        if (item->type() == Plant::Type)
        {
            Plant* plant = qgraphicsitem_cast<Plant *> (item);
            if(plant->type_)
            {
                plant->Crazy = 0;
                plant->Aoe = 0;
                plant->Ice = 0;
                plant->Fire = -1;
            }
            else
            {
                plant->Crazy = -1;
                plant->Aoe = -1;
                plant->Ice = -1;
                plant->Fire = 0;
            }
            return;
        }
}

