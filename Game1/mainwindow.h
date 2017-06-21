#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QDebug>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readResults();

    void on_action_4_triggered();

    void on_Exit_clicked();

    void on_action_3_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_Game1_clicked();

    void on_Game2_clicked();

    void on_Game3_clicked();

    void on_Game4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
