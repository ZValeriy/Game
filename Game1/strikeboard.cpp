#include <QtWidgets>

#include "strikeboard.h"

StrikeBoard::StrikeBoard(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();
}

void StrikeBoard::start()
{
    if (isPaused)
        return;

    isStarted = true;
    numLinesRemoved = 0;
    score = 0;
    level = 1;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    createStrike();
    timer.start(timeoutTime(), this);
}

void StrikeBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}

void StrikeBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();

    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Пауза"));
        return;
    }

    int boardTop = rect.bottom() - BoardHeight*squareHeight();
    drawSquare(painter, rect.left() + strikeX * squareWidth(), boardTop + strikeY * squareHeight());

//    for (int i = 0; i < BoardHeight; ++i) {
//        for (int j = 0; j < BoardWidth; ++j) {
//            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
//            if (shape != NoShape)
//                drawSquare(painter, rect.left() + j * squareWidth(),
//                           boardTop + i * squareHeight(), shape);
//        }
//    }

//    if (curPiece.shape() != NoShape) {
//        for (int i = 0; i < 4; ++i) {
//            int x = curX + curPiece.x(i);
//            int y = curY - curPiece.y(i);
//            drawSquare(painter, rect.left() + x * squareWidth(),
//                       boardTop + (BoardHeight - y - 1) * squareHeight(),
//                       curPiece.shape());
//        }
//    }
}

void StrikeBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        tryMoveStrike(strikeX - 1);
        break;
    case Qt::Key_Right:
        tryMoveStrike(strikeX + 1);
        break;
    case Qt::Key_Space:
//        dropDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void StrikeBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {

    } else {
        QFrame::timerEvent(event);
    }
}


void StrikeBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoPoints;
}

void StrikeBoard::createStrike()
{
    strikeX = BoardWidth / 2 + 1;
    strikeY = BoardHeight - 1;
}

bool StrikeBoard::tryMoveStrike(int newX)
{
    if (newX < 0 || newX >= BoardWidth)
        return false;

    strikeX = newX;
    update();

    return true;
}

void StrikeBoard::drawSquare(QPainter &painter, int x, int y)
{
//    static const QRgb colorTable[8] = {
//        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
//        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
//    };

    QColor color = 0xCC6666;
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
