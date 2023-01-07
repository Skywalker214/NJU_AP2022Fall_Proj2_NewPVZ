#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSound>
#include <QPushButton>
#include "helper.h"
#include "gamewindow.h"
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Map_Init();
    void Start_Game();
    void Map_Edit();

    MapInfo map_info;
    QGraphicsScene *scene;
    QGraphicsView *view;
};
#endif // MAINWINDOW_H
