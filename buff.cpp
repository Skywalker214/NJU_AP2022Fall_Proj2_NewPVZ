#include "buff.h"

Buff::Buff(QString n)
{
    name = n;
    counter = 0;
    available = 0;
    if(n == "Crazy")
    {
        cool = 100;
        type = 1;
    }
    else if(n == "Ice")
    {
        cool = 100;
        type = 1;
    }
    else if(n == "Aoe")
    {
        cool = 100;
        type = 1;
    }
    else if(n == "Fire") //aka bleeding
    {
        cool = 100;
        type = 0;
    }
}

QRectF Buff::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}

void Buff::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-50, -30, 100, 60), QPixmap(":/images/Buff/" + name + ".png"));
    if (counter * available < cool)
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        if(!available)
            painter->drawRect(QRectF(-50, -30, 100, 60));
        else
            painter->drawRect(QRectF(-50, -30, 100, 60 * (1 - qreal(counter) / qreal(cool))));
    }
}

void Buff::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter < cool)
        counter++;
}

void Buff::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (counter * available < cool)
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);
}

void Buff::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
        return;
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;
    QImage image(":/images/Buff/" + name + ".png");
    mime->setText(name);
    mime->setImageData(image);
    drag->setMimeData(mime);
    //drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35, 35));
    drag->exec();
    setCursor(Qt::ArrowCursor);
}

void Buff::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
