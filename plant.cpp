#include "plant.h"

Plant::Plant()
{
    movie = nullptr;
    hp = atk = counter = time = 0;
    type_ = Aoe = Crazy = Ice = Fire = -1;
    range = 0.0;
}

Plant::~Plant()
{
    delete movie;
}

QRectF Plant::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), movie->currentImage());
}

bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && sqrt(qPow(other->x() - x(), 2) + qPow(other->y() - y(), 2)) < range;
}

int Plant::type() const
{
    return Type;
}

void Plant::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}
