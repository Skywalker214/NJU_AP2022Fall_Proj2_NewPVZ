#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QTimer>
#include <QDebug>
#include "helper.h"
#include "map.h"
#include "shop.h"
#include "button.h"
#include "shovel.h"
#include "buffshop.h"
#include "buffcleaner.h"

#include "basiczombie.h"
#include "peashooter.h"
#include "bonkchoy.h"


class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(MapInfo mi, QWidget *parent = nullptr);
    ~GameWindow() override;

    void add_zombies();

    MapInfo map_info;
    QSound *sound;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int add_zombies_count;
};

#endif // GAMEWINDOW_H
