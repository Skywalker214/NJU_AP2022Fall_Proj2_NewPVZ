#include "zombie.h"

Zombie::Zombie()
{
    movie = head = nullptr;
    hp = sumhp = atk = state = dest = 0;
    //slow = 0;
    speedup = flash = 0;
    flash_count = -1;
    speed = 0.0;
    onfire = 0;
    onfire_count = 0;
    frozen = 0;
    frozen_count = 0;
}

Zombie::~Zombie()
{
    delete movie;
    delete head;
}

QRectF Zombie::boundingRect() const
{
    return QRectF(-80, -100, 200, 140);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QImage image = movie->currentImage();
    painter->drawImage(QRectF(-70, -100, 140, 140), image);
    if (head)
    {
        image = head->currentImage();
        painter->drawImage(QRectF(0, -100, 140, 140), image);
    }
    if(flash)
    {
        painter->drawImage(QRectF(-5, -95, 10, 10), QImage(":/images/Buff/flash.png"));
        if(flash_count < int(10 * 1000 / 33))
        {
            QBrush brush(QColor(0, 0, 0, 200));
            painter->setBrush(brush);
            painter->drawRect(QRectF(-5, -95, 10, 10 * (1 - (qreal(flash_count) / qreal(int(10 * 1000 / 33))))));
        }
    }
    if(speedup)
        painter->drawImage(QRectF(5, -95, 10, 10), QImage(":/images/Buff/haste.png"));
    painter->drawImage(QRectF(-20, -82, 50, 10), QImage(":/images/Interface/HPBar0.png"));
    QBrush brush1(QColor(0, 0, 0, 200));
    painter->setBrush(brush1);
    painter->drawRect(QRectF(-20, -82, 50 * (1.0 - (qreal(hp) / qreal(sumhp))), 10));
}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Plant::Type && sqrt(qPow(other->x() - x(), 2) + qPow(other->y() - y(), 2)) < 25;
}

int Zombie::type() const
{
    return Type;
}

void Zombie::setMovie(QString path)
{
    if (movie)
        delete movie;
    movie = new QMovie(path);
    movie->start();
}

void Zombie::setHead(QString path)
{
    if (head)
        delete head;
    head = new QMovie(path);
    head->start();
}
