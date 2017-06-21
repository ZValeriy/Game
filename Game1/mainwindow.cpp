#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QErrorMessage>
#include <string>
#include "tetrixwindow.h"
#include "strikeboard.h"
#include "strikewindow.h"
#include "widget.h"
#include "PPwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void deleteResults()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Предупреждение");
    msgBox.setText("Внимание!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText("Рекорды будут очищены.\nДля продолжения нажмите 'OK'");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Cancel:
         msgBox.close();
         break;
      case QMessageBox::Ok:
        QFile file1("C:/QT Proj/Game1/Game1.txt");
        if (file1.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        file1.close();
        }

        QFile file2("C:/QT Proj/Game1/Game2.txt");
        if (file2.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        file2.close();
        }

        QFile file3("C:/QT Proj/Game1/Game3.txt");
        if (file3.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        file3.close();
        }
         break;

    }
}

void MainWindow::readResults()
{
    QFile file1("C:/QT Proj/Game1/Game1.txt");
    if (!file1.open(QIODevice::ReadOnly))
    {
        (new QErrorMessage(this))->showMessage("Ошибка чтения файла с рекордами");
    }

    QByteArray rec1 = file1.readAll();
    if(rec1 == "")
        rec1 = "0";


    QFile file2("C:/QT Proj/Game1/Game2.txt");

    if (!file2.open(QIODevice::ReadOnly))
    {
        (new QErrorMessage(this))->showMessage("Ошибка чтения файла с рекордами");
    }

    QByteArray rec2 = file2.readAll();
    if(rec2 == "")
        rec2 = "0";

    QFile file3("C:/QT Proj/Game1/Game3.txt");

    if (!file3.open(QIODevice::ReadOnly))
    {
        (new QErrorMessage(this))->showMessage("Ошибка чтения файла с рекордами");
    }


    QByteArray rec3 = file3.readAll();
    if(rec3 == "")
        rec3 = "0";

    QMessageBox * msgBox = new QMessageBox();
    msgBox->setWindowTitle("Рекорды");
    QString recs;
    recs = "Рекорд Игры1: " + rec1 + "\n\nРекорд Игры2: " + rec2 + "\n\nРекорд Игры3: " + rec3;
    msgBox->setText(recs);
    msgBox->show();
}

void MainWindow::on_action_4_triggered()
{


    QMessageBox msgBox;
    msgBox.setWindowTitle("Справка");
    msgBox.setText("Приветствуем Вас в игре \"ТехноТет\"и желаем приятных впечатлений\n\n"\
                   "4 игры:\n"\
                   "Бла Бла: цель, управление...\n\n"\
                   "Бла Бла2: цель, управление...\n\n"\
                   "Бла Бла3: цель, управление...\n\n"\
                  );
    msgBox.exec();

}

void MainWindow::on_Exit_clicked()
{
    this->close();
}

void MainWindow::on_action_3_triggered()
{
    QMessageBox * msgBox = new QMessageBox();
    msgBox->setWindowTitle("О программе");
    msgBox->setText("ТехноТет\nVersion 1.0, 21 июня\n2017\n");
    msgBox->exec();
}

void MainWindow::on_action_triggered()
{
    readResults();
}

void MainWindow::on_action_2_triggered()
{
    deleteResults();
}

void MainWindow::on_Game1_clicked()
{
    TetrixWindow * tetr = new TetrixWindow();
    tetr->show();

}

void MainWindow::on_Game2_clicked()
{
    StrikeWindow * str = new StrikeWindow();
    str->show();
}

void MainWindow::on_Game3_clicked()
{
    Widget * sn = new Widget();
    sn->show();
}

void MainWindow::on_Game4_clicked()
{
    PingWindow * pp = new PingWindow();
    pp->show();
}
