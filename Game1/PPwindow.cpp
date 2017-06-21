#include "PPwindow.h"
#include "ui_PPwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "move.h"
#include <QPen>
#include <QResizeEvent>
#include <QDebug>

PingWindow::PingWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PingWindow),
    Score ( 0 )
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsRectItem *p1 = new QGraphicsRectItem(0, 0, 80, 20);
    p1->setBrush(QBrush(Qt::black));
    QGraphicsRectItem *p2 = new QGraphicsRectItem(0, 0, 80, 20);
    p2->setBrush(QBrush(Qt::cyan));

    QGraphicsEllipseItem *ball = new QGraphicsEllipseItem(0, 0, 15, 15);
    ball->setBrush(QBrush(Qt::blue));

    ui->boardView->setScene(scene);

    Loop = new Moving(*scene, p1, p2, ball, this);
    QSize (scene->sceneRect().size().width() + 10, scene->sceneRect().size().height() + 10);
   // ui->boardView->setMinimumSize(100, 300);
    //resize(minimumSize());
    ui->boardView->installEventFilter(Loop);

    QObject::connect(Loop, SIGNAL(goal(int)),
                     this, SLOT(addScore(int)));
}

PingWindow::~PingWindow()
{
    delete ui;
}

void PingWindow::addScore(int count)
{
    Score += count;
    ui->lcdNumber->display(Score);
}
