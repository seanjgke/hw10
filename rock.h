#ifndef ROCK_H
#define ROCK_H

#include <QWidget>
#include <QString>
#include <QLabel>

namespace Ui {
class rock;
}

class rock : public QLabel
{
    Q_OBJECT

public:
    explicit rock(QWidget *parent = 0);
    void change_position(QString a);
    ~rock();

    QString color;      //record the color
    QPoint coordinates; //record the position

private:
    Ui::rock *ui;
};

#endif // ROCK_H
