#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Map_Init();

    this->setFixedSize(900,600);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 900, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    view = new QGraphicsView(scene, this);
    view->resize(902, 602);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/Interface/main.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QPushButton *pb1=new QPushButton(this);
    pb1->setIcon(QIcon(":/images/Interface/button1.png"));
    pb1->setIconSize(QSize(120,60));
    pb1->move(300, 500);

    QPushButton *pb2=new QPushButton(this);
    pb2->setIcon(QIcon(":/images/Interface/button2.png"));
    pb2->setIconSize(QSize(120, 60));
    pb2->move(480, 500);

    connect(pb1, &QPushButton::clicked, this, &MainWindow::Start_Game);
    connect(pb2, &QPushButton::clicked, this, &MainWindow::Map_Edit);
    view->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::Map_Init()
{
    qDebug("map init");
    int temp[5][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {3, 1, 1, 1, 1, 1, 1, 1, 2},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {3, 1, 1, 1, 1, 1, 1, 1, 2},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    map_info.x = 5;
    map_info.y = 9;
    for(int i = 0; i < map_info.x; i++)
    {
        std::vector<int> line;
        for(int j = 0; j < map_info.y; j++)
            line.push_back(temp[i][j]);
        map_info.map.push_back(line);
    }
    map_info.zombie_birthplace.push_back(std::pair<int, int>(1,8));
    map_info.zombie_birthplace.push_back(std::pair<int, int>(3,8));
    map_info.home.push_back(std::pair<int, int>(1,0));
    map_info.home.push_back(std::pair<int, int>(3,0));
    std::vector<std::pair<int, int>> way1;
    for(int i = 8; i >= 0; i--)
    {
        way1.push_back(std::pair<int, int>(1,i));
    }
    map_info.routes.push_back(way1);
    std::vector<std::pair<int, int>> way2;
    for(int i = 8; i >= 0; i--)
    {
        way2.push_back(std::pair<int, int>(3,i));
    }
    map_info.routes.push_back(way2);
}

void MainWindow::Start_Game()
{
    this->hide();
    GameWindow *gw = new GameWindow(map_info);
    gw->show();
}

void MainWindow::Map_Edit()
{
    qDebug("map edit");
    map_info.map.clear();
    map_info.zombie_birthplace.clear();
    map_info.home.clear();
    map_info.routes.clear();
    QString file_name=QFileDialog::getOpenFileName(this,tr("请导入地图文件"));
    if(!file_name.isNull())
    {
        QFile file(file_name);
        file.open(QFile::ReadOnly);
        QTextStream in(&file);
        int num_of_way;
        in>>map_info.x>>map_info.y>>num_of_way;
        for(int i = 0; i < map_info.x; i++)
        {
            std::vector<int> line;
            for(int j = 0; j < map_info.y; j++)
            {
                int temp;
                in>>temp;
                if(temp == 2)
                    map_info.zombie_birthplace.push_back(std::pair<int, int>(i, j));
                if(temp == 3)
                    map_info.home.push_back(std::pair<int, int>(i, j));
                line.push_back(temp);
            }
            map_info.map.push_back(line);
        }
        for(int i = 0; i < num_of_way; i++)
        {
            int tx = 0, ty = 0;
            std::vector<std::pair<int, int>> way;
            while(tx != -1)
            {
                in>>tx>>ty;
                if(tx != -1)
                    way.push_back(std::pair<int, int>(tx, ty));
            }
            map_info.routes.push_back(way);
        }
        file.close();
    }
}
