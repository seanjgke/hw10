#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "gameboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void stack_show_instruction();
    void stack_show_main();

    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();
    void game_over();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    gameboard* board;
    QStackedWidget* stack;
};

#endif // MAINWINDOW_H
