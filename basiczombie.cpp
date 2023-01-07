#include "basiczombie.h"

BasicZombie::BasicZombie(std::vector<std::pair<int, int>> r, int su, int f)
{
    hp = sumhp = 270;
    atk = 100 * 33 / 1000;
    //speed = 100 * 33 / 1000 / 4.7;
    speed = 1;
    dest = 0;
    route = r;

    speedup = su;
    flash = f;
    if(flash)
        flash_count = int(10 * 1000 / 33) + 1;
    else
        flash_count = -1;

    if(speedup)
        speed *= 2;

    onfire = 0;
    onfire_count = 0;
    frozen = 0;
    frozen_count = 0;

    if (qrand() % 3 == 0)
        setMovie(":/images/Zombies/BasicZombie/Zombie.gif");
    else if(qrand() % 3 == 1)
        setMovie(":/images/Zombies/BasicZombie/Zombie2.gif");
    else
        setMovie(":/images/Zombies/BasicZombie/Zombie3.gif");
}

void BasicZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if(onfire)
    {
        hp -= 1;
        onfire_count++;
        if(onfire_count > 50)
        {
            onfire = 0;
            onfire_count = 0;
        }
    }
    if (hp <= 0)
    {
        if (state != 2)
        {
            Drops *d1 = new Drops("Sun");
            d1->setPos(x(), y());
            scene()->addItem(d1);
            int bf = qrand() % 100;
            if(bf < 10)
            {
                Drops *d2 = new Drops("Crazy");
                d2->setPos(x(), y());
                scene()->addItem(d2);
            }
            else if(bf < 20)
            {
                Drops *d2 = new Drops("Ice");
                d2->setPos(x(), y());
                scene()->addItem(d2);
            }
            else if(bf < 30)
            {
                Drops *d2 = new Drops("Aoe");
                d2->setPos(x(), y());
                scene()->addItem(d2);
            }
            else if(bf < 40)
            {
                Drops *d2 = new Drops("Fire");
                d2->setPos(x(), y());
                scene()->addItem(d2);
            }
            state = 2;
            setMovie(":/images/Zombies/BasicZombie/ZombieDie.gif");
            setHead(":/images/Zombies/BasicZombie/ZombieHead.gif");
        }
        else if (movie->currentFrameNumber() == movie->frameCount() - 1)
            delete this;
        return;
    }
    if(frozen)
    {
        movie->stop();
        frozen_count++;
        if(frozen_count > int(3 * 1000 / 33))
        {
            frozen = 0;
            frozen_count = 0;
            movie->start();
        }
        return;
    }
    if(flash)
        flash_count++;
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        if(flash && flash_count > int(10 * 1000 / 33))
        {
            qDebug("flash!");
            dest++;
            setX(route[dest].second * 100 + 50);
            setY(route[dest].first * 100 + 50);
            flash_count = 0;
        }
        else
        {
            Plant *plant = qgraphicsitem_cast<Plant *>(items[0]);
            plant->hp -= atk;
            if (state != 1)
            {
                state = 1;
                setMovie(":/images/Zombies/BasicZombie/ZombieAttack.gif");
            }
            return;
        }
    }
    if (state)
    {
        state = 0;
        if (qrand() % 3 == 0)
            setMovie(":/images/Zombies/BasicZombie/Zombie.gif");
        else if(qrand() % 3 == 1)
            setMovie(":/images/Zombies/BasicZombie/Zombie2.gif");
        else
            setMovie(":/images/Zombies/BasicZombie/Zombie3.gif");
    }

    //move forward
    //qDebug("%f %f", x(), y());
    //if(abs(x() - (route.end()->second * 100 + 50)) < 15 && abs(y() - (route.end()->first * 100 + 50)) < 15)
    if(x() == (route[route.size() - 1].second * 100 + 50) && y() == (route[route.size() - 1].first * 100 + 50))
    {
        qDebug("get brain");
        delete this;
    }
    if(x() == (route[dest].second * 100 + 50) && y() == (route[dest].first * 100 + 50))
        dest++;
    else if(x() == (route[dest].second * 100 + 50))
    {
        if(y() < (route[dest].first * 100 + 50))
            setY(y() + speed);
        else
            setY(y() - speed);
    }
    else if(y() == (route[dest].first * 100 + 50))
    {
        if(x() < (route[dest].second * 100 + 50))
            setX(x() + speed);
        else
            setX(x() - speed);
    }
}

