#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include "rock.h"
//#include "mainwindow.h"

namespace Ui {
class gameboard;
}

class gameboard : public QWidget
{
    Q_OBJECT

signals:
       void game_over();

public slots:
       void update_cave();

public:
    explicit gameboard(QWidget *parent = 0, int difficult = 5);

    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *e);

    void next_level();

    ~gameboard();

private:
    Ui::gameboard *ui;

    int space;
    int upper;
    int lower;

    int p_height;
    int r_height;

    int level;
    int score;
    QLabel* score_widget;

    QTimer* timer;
    int time_interval;
    std::vector<std::vector<rock*> > labels;


};

#endif // GAMEBOARD_H
