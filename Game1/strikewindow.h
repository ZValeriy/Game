#ifndef STRIKEWINDOW_H
#define STRIKEWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class StrikeBoard;

class StrikeWindow : public QWidget
{
    Q_OBJECT

public:
    StrikeWindow();

private:
    QLabel *createLabel(const QString &text);

    StrikeBoard *board;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
};

#endif // STRIKEWINDOW_H
