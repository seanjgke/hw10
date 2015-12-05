#include "gameboard.h"
#include "mainwindow.h"
#include "ui_gameboard.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPixmap>
#include <QString>
#include <iostream>
#include <QMenuBar>
#include <QTextEdit>
#include <QMessageBox>
#include <ctime>
#include <QTimer>

gameboard::gameboard(QWidget *parent, int difficult) :
    QWidget(parent),
    ui(new Ui::gameboard),
    space(difficult)
{
    ui->setupUi(this);

    //Initialize the basic game data
    upper = 4;
    lower = 4;
    if (space >= 4) upper = 3;
    if (space == 5) lower = 3;
    r_height = upper;
    level = 1;
    score = 0;

    //the upper part of the game board, showing the score
    QVBoxLayout *part2 = new QVBoxLayout;
    score_widget = new QLabel("Score: 0");
    part2->addWidget(score_widget);

    QWidget *content = new QWidget;
    QGridLayout *layout = new QGridLayout(content);

    layout->setMargin(0);
    layout->setSpacing(0);

    labels.resize(11);

    //Initialize the game board
    for(int i = 0; i < 11 ; i++){
        labels[i].resize(20);
        for(int j = 0; j < 20;j++){
        labels[i][j] = new rock;
        labels[i][j]->setFixedSize(30,30);

        //Set black boxes
        if(i <= (upper-1) || i>=(upper+space)){
            labels[i][j]->setStyleSheet("QLabel {background-color : black;}");
            labels[i][j]->coordinates = QPoint(i,j);
            labels[i][j]->color = QString("black");
        }

        //Set the blue box in the middle of the first column
        else if(i==5 && j==0){
                labels[i][j]->setStyleSheet("QLabel {background-color : skyblue;}");
                p_height = 5;
        }

        //Set white boxes(space for blue box)
        else{
            labels[i][j]->setStyleSheet("QLabel {background-color : white;}");
            labels[i][j]->coordinates = QPoint(i,j);
            labels[i][j]->color = QString("white");
        }
        layout -> addWidget(labels[i][j],i,j);
        }
    }

    part2->addWidget(content);
    this->setLayout(part2);

    connect(this, SIGNAL(game_over()), parent, SLOT(game_over()));

    //Initialize the timer to update game board
    timer = new QTimer;
    time_interval = 320;
    timer->setInterval(time_interval);
    timer->start();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_cave()));
}

gameboard::~gameboard()
{
    delete ui;
}

//Activate keyPressEvent and connect keys
void gameboard::keyPressEvent(QKeyEvent *event)
{
    //Move the blue box up when up is pressed
    if (event->key() == Qt::Key_Up){
        labels[p_height][0]->change_position("white");
        --p_height; //update new height
        if(labels[p_height][0]->color != "black")
            labels[p_height][0]->change_position("skyblue");
        else
            this->game_over();
    }
    //Move the blue box down when down is pressed
    else if (event->key() == Qt::Key_Down){
        labels[p_height][0]->change_position("white");
        ++p_height; //update new height
        if(labels[p_height][0]->color != "black")
            labels[p_height][0]->change_position("skyblue");
        else
           this->game_over();
    }


}

void gameboard::showEvent(QShowEvent *e) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}

//Function that updates the game board according to the timer
void gameboard::update_cave(){

    //Game over in hit the black box in front
    if (labels[p_height][1]->color == "black") {this->game_over(); return;}

    //First two for loop update the color of first column
    for (int i = 0; i < p_height; i++){
        labels[i][0]->change_position(labels[i][1]->color);
    }
    for (int i = (p_height+1); i < 11; i++){
        labels[i][0]->change_position(labels[i][1]->color);
    }

    //Update column 1 to 19
    for (int j = 1; j<19; j++){
        for (int i = 0; i < 11; i++){
            labels[i][j]->change_position(labels[i][j+1]->color);
        }
    }

   // srand(time(NULL));
    int change_rock = rand()%5;

    //Randomly generate new  black boxes for the column 20
    switch (change_rock) {
    case 1:
        if(r_height<(11-space)){
            labels[r_height][19]->change_position("black");
            labels[r_height+space][19]->change_position("white");
            r_height++;
        }
        break;
    case 2:
        if(r_height>0){
            r_height--;
            labels[r_height][19]->change_position("white");
            labels[r_height+space][19]->change_position("black");
        }
        break;
    case 3:
        if(r_height<(10-space)){
            labels[r_height][19]->change_position("black");
            labels[r_height+1][19]->change_position("black");
            labels[r_height+space][19]->change_position("white");
            labels[r_height+space+1][19]->change_position("white");
            r_height+=2;
        }
        break;
    case 4:
        if(r_height>1){
            r_height-=2;
            labels[r_height][19]->change_position("white");
            labels[r_height+1][19]->change_position("white");
            labels[r_height+space][19]->change_position("black");
            labels[r_height+space+1][19]->change_position("black");
        }
        break;
    default:
        break;
    }

    //update score
    ++score;
    score_widget->setText("Score: "+ QString::number(score) );

    //enter next level when scoere reach every 100.
    if(score % 100 == 0) next_level();

    return;

}


//A function that shorten the time interval of the timer to update the game board, making the game harder
void gameboard::next_level(){
    ++level; //update level

    //discounnect the update function
    QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(update_cave()));

    //reminder the player for the next level
    QMessageBox::warning(this, "Congradualation!" ,"Enter the next Level! Level: " + QString::number(level));

    //update timer
    time_interval *= 0.83;
    if(time_interval<2) game_over();

    //reconnect the update function with new timer
    timer->setInterval(time_interval);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_cave()));
}
