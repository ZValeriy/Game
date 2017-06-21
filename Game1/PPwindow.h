#include <QMainWindow>
class Moving;

namespace Ui {
class PingWindow;
}

class PingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PingWindow(QWidget *parent = 0);
    ~PingWindow();

private slots:
    void addScore(int count);

private:
    Ui::PingWindow *ui;
    Moving *Loop;
    int Score;
};
