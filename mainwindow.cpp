#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
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
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stack = new QStackedWidget;
    QWidget* central = new QWidget;
    QWidget* main_menu = new QWidget;
    QWidget* instructions = new QWidget;


    QVBoxLayout *part1 = new  QVBoxLayout;
    //set the title
    QLabel *title= new QLabel("Start the Game!");
    title->setAlignment(Qt::AlignCenter);
    title->setFixedHeight(70);
    part1->addWidget(title);

    //set up the main window
    QPushButton* check_instruction = new QPushButton("Instructions");
    part1->addWidget(check_instruction);
    QWidget *bottom = new QWidget;
    QLabel *levels = new QLabel("         Select difficulty:");
    QWidget *menue = new QWidget;
    QPushButton *easy = new QPushButton("Easy");
    QPushButton *medium = new QPushButton("Medium");
    QPushButton *hard = new QPushButton("Hard");
    QVBoxLayout *buttons = new QVBoxLayout(menue);
    buttons->addWidget(easy);
    buttons->addWidget(medium);
    buttons->addWidget(hard);
    QHBoxLayout *h = new QHBoxLayout(bottom);
    h->addWidget(levels);
    h->addWidget(menue);
    part1->addWidget(bottom);

    //connect the pushbuttons with corresponding slots
    QObject::connect(check_instruction,SIGNAL(clicked()),this,SLOT(stack_show_instruction()));
    QObject::connect(easy,SIGNAL(clicked()),this,SLOT(easy_game_begin()));
    QObject::connect(medium,SIGNAL(clicked()),this,SLOT(medium_game_begin()));
    QObject::connect(hard,SIGNAL(clicked()),this,SLOT(hard_game_begin()));

    main_menu->setLayout(part1);


    //set up instruction window
    QVBoxLayout* inst = new  QVBoxLayout;
    QTextEdit* details = new QTextEdit("Use your arrow keys \"up\" and \"down\" to control the blue box not to hit the black boxes on the top and bottom. Once the blue box hits a black box, the game is over. The longer you stay alive, the higher score you wil get. Once you reach a certain score, you will enter next level and the black boxes will move faster at the same time. There are three difficulties: easy, medium and hard. The harder it goes, the less space the blue box will have, and more black boxes will come out.");
    QPushButton* go_to_main = new QPushButton("Go Back");
    QObject::connect(go_to_main,SIGNAL(clicked()),this,SLOT(stack_show_main()));
    inst->addWidget(details);
    inst->addWidget(go_to_main);
    instructions->setLayout(inst);

    //set stack for the main window and instruction window
    stack->insertWidget(0, main_menu);
    stack->insertWidget(1, instructions);

    QVBoxLayout* stacked_layout = new QVBoxLayout;
    stacked_layout->addWidget(stack);

    central -> setLayout(stacked_layout);
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stack_show_instruction(){
   stack->setCurrentIndex(1);
};

void MainWindow::stack_show_main(){
   stack->setCurrentIndex(0);
};

//begin the easy game
void MainWindow::easy_game_begin(){
    board = new gameboard(this, 5);
    this->setCentralWidget(board);
};

//begin the medium game
void MainWindow::medium_game_begin(){
    board = new gameboard(this, 4);
    this->setCentralWidget(board);
};

//begin the hard game
void MainWindow::hard_game_begin(){
    board = new gameboard(this, 3);
    this->setCentralWidget(board);
};

//redisplay the main window when game is over
void MainWindow::game_over() {
    board = NULL;
    ui->setupUi(this);

    //show the three difficulty levels again
    stack = NULL;
    QPushButton *easy1 = new QPushButton("Easy");
    QPushButton *medium1 = new QPushButton("Medium");
    QPushButton *hard1 = new QPushButton("Hard");

    //connect corresponding slots
    QObject::connect(easy1,SIGNAL(clicked()),this,SLOT(easy_game_begin()));
    QObject::connect(medium1,SIGNAL(clicked()),this,SLOT(medium_game_begin()));
    QObject::connect(hard1,SIGNAL(clicked()),this,SLOT(hard_game_begin()));

    //set the layout
    QVBoxLayout *part3 = new  QVBoxLayout;
    QLabel*title = new QLabel("Game Over!");
    QLabel *restart = new QLabel("Start Again:");
    QFont f( "Arial", 20, QFont::Bold);
    title->setFont(f);
    title->setAlignment(Qt::AlignCenter);
    part3->addWidget(title);
    part3->addWidget(restart);
    part3->addWidget(easy1);
    part3->addWidget(medium1);
    part3->addWidget(hard1);

    centralWidget()->setLayout(part3);
}

