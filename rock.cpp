#include "rock.h"
#include "ui_rock.h"

rock::rock(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::rock)
{
    ui->setupUi(this);
}

rock::~rock()
{
    delete ui;
}

//helper function for updating the game board
void rock::change_position(QString a) {
    this->setStyleSheet("QLabel{background-color:"+a+"}");
    color = a;
}
