#include <QObject>
#include <QGraphicsScene>
//class QGraphicsItem;
//class QTimer;

class Moving : public QObject
{
    Q_OBJECT
public:
    explicit Moving(QGraphicsScene & scene, QGraphicsItem *p1, QGraphicsItem *p2, QGraphicsItem *ball, QObject *parent);

protected:
    virtual bool eventFilter(QObject *, QEvent *use);

signals:
    void goal(int p);

private slots:
    void time();

private:
    qreal calculateP2Shift();
    QGraphicsScene & Scene;
    QGraphicsItem *P1, *P2, *Ball;
    QTimer *Timer;

    QPointF BallShift;
    qreal P1Shift;
    qreal P2Shift;
};
