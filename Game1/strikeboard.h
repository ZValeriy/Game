#ifndef STRIKEBOARD_H
#define STRIKEBOARD_H

#include <QBasicTimer>
#include <QFrame>

enum StrikePoints { NoPoints, IsPoints};

class StrikeBoard : public QFrame
{
    Q_OBJECT

public:
    StrikeBoard(QWidget *parent = 0);

public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    enum { BoardWidth = 10, BoardHeight = 22 };

    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();

    void createStrike();
    bool tryMoveStrike(int newX);
    void drawSquare(QPainter &painter, int x, int y);

    QBasicTimer timer;
    bool isStarted;
    bool isPaused;
    int strikeX;
    int strikeY;
    int numLinesRemoved;
    int score;
    int level;

    StrikePoints board[BoardWidth * BoardHeight];
};

#endif // STRIKEBOARD_H
