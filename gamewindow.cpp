#include "gamewindow.h"

GameWindow::GameWindow(MapInfo mi, QWidget *parent) : QMainWindow(parent)
{
    map_info = mi;
    add_zombies_count = int(5 * 1000 / 33);

    this->setFixedSize(1200, 1000);
    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound = new QSound(":/Grazy Dave.wav");
    sound->setLoops(QSound::Infinite);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1200, 1000);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Map* map = new Map(map_info);
    map->setPos(0, 0);
    scene->addItem(map);
    Shop* shop = new Shop();
    shop->setPos(270, 955);
    scene->addItem(shop);
    Button* btn = new Button(sound, timer);
    btn->setPos(1120, 20);
    scene->addItem(btn);
    Shovel* shovel = new Shovel();
    shovel->setPos(600, 960);
    scene->addItem(shovel);
    BuffShop* buffshop = new BuffShop();
    buffshop->setPos(1150, 200);
    scene->addItem(buffshop);
    BuffCleaner* buffcleaner = new BuffCleaner();
    buffcleaner->setPos(700, 960);
    scene->addItem(buffcleaner);

    view = new QGraphicsView(scene, this);
    view->resize(1202, 1002);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/Interface/background.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &GameWindow::add_zombies);
    sound->play();
    timer->start(33);
    view->show();
}

GameWindow::~GameWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

void GameWindow::add_zombies()
{
    add_zombies_count++;
    if(add_zombies_count > int(5 * 1000 / 33))
    {
        int pos = qrand() % map_info.zombie_birthplace.size();
        int su = (qrand() % 100 > 75);
        int f = (qrand() % 100 > 75);
        BasicZombie *bz = new BasicZombie(map_info.routes[pos], su, f);
        bz->setPos(map_info.zombie_birthplace[pos].second * 100 + 50, map_info.zombie_birthplace[pos].first * 100 + 50);
        scene->addItem(bz);
        add_zombies_count = qrand() % (int(3 * 1000 / 33));
    }
}
