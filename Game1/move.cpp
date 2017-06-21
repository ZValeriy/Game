#include "move.h"
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>

Moving::Moving(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball, QObject *parent) :
    QObject(parent),
    Scene ( scene ),
    P1 ( p1 ),
    P2 ( p2 ),
    Ball ( ball ),
    BallShift ( -3, -3 ),
    P1Shift( 0 ),
    P2Shift( 0 )
{
    Scene.setSceneRect(0, 0, 350, 320);
    Scene.addItem(P1);
    Scene.addItem(P2);
    Scene.addItem(Ball);

    P1->setPos(135, 5);
    P2->setPos(135, 300);
    Ball->setPos(150, 150);

    Timer = new QTimer(this);
    Timer->setInterval(12);
    Timer->start();
    QObject::connect(Timer, SIGNAL(timeout()), this, SLOT(time()));
}

void Moving::time()
{
    qreal nX = Ball->pos().x() + BallShift.x();
    qreal nY = Ball->pos().y() + BallShift.y();

    qreal pnX = P1->pos().x() + P1Shift;
    qreal p2nX = P2->pos().x() + P2Shift;

    if ( ( nX + Ball->boundingRect().left() < Scene.sceneRect().left() ) || ( nX + Ball->boundingRect().right() > Scene.sceneRect().right() ) )
    {
        BallShift.rx() *= -1;
    }

    if ( ( nY < 0 ) || ( nY + Ball->boundingRect().bottom() > Scene.sceneRect().bottom() ) )
    {
        emit goal(nY / abs(nY));
        BallShift.ry() *= -1;
    }

    if ( ( pnX + P1->boundingRect().left() < Scene.sceneRect().left() ) || ( pnX + P1->boundingRect().right() > Scene.sceneRect().right() ) )
    {
        P1Shift = 0;
    }

    if ( ( p2nX + P1->boundingRect().left() < Scene.sceneRect().left() ) || ( p2nX + P1->boundingRect().right() > Scene.sceneRect().right() ) )
    {
        P2Shift = 0;
    }

    if ( ( P1->collidesWithItem(Ball) ) && ( BallShift.y() < 0 ) )
    {
        BallShift.ry() *= -1;
    }

    if ( ( P2->collidesWithItem(Ball) ) && ( BallShift.y() > 0 ) )
    {
        BallShift.ry() *= -1;
    }

    if ( qrand() % 10 == 5 )
    {
        P2Shift = calculateP2Shift();
    }


    Ball->moveBy(BallShift.x(), BallShift.y());
    P1->moveBy(P1Shift, 0);
    P2->moveBy(P2Shift, 0);
}

bool Moving::eventFilter(QObject *purpose, QEvent *use)
{
    Q_UNUSED(purpose);

    bool handled = false;
    if ( use->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = (QKeyEvent *)use;

        if ( keyEvent->key() == Qt::Key_Left )
        {
            P1Shift = (P1Shift == 0 ? -5 : 0);
            handled = true;
        }
        else if ( keyEvent->key() == Qt::Key_Right )
        {
            P1Shift  = (P1Shift == 0 ? 5 : 0);
            handled = true;
        }
    }

    return handled;
}

qreal Moving::calculateP2Shift()
{
    qreal var = 0;

    if ( Ball->pos().x() + BallShift.x() > P2->sceneBoundingRect().right() )
    {
        var = 10;
    }
    else if ( Ball->pos().x() + BallShift.x() < P2->sceneBoundingRect().left() )
    {
        var = -10;
    }

    return var;
}

