#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QSet>
#include <vector>
#include <QDataStream>
#include "functions.h"

class snake : public QObject
{
    Q_OBJECT
public:
    snake(int snakeNum, int startLen);
    snake(snake *other);

    void changeDir(int dir);
    void setCanvas(int **canvas);
    void move();
    void auto_move();
    void init_snake_on_canvas();
    int getSpeedCounter();
    int getSpeed();
    int &direct();
    bool &qAlive();     //query if alive
    int snakeN;        //nth snake (1 or 2)
    int startL;
    int lifeN;         //number of life
    QQueue<QPoint> *snakeNode;

    friend QDataStream &operator<<(QDataStream &, const snake &);
    friend QDataStream &operator>>(QDataStream &, snake &);

private:

    static const int CANVAS_WIDTH_PIXEL = 20;
    static const int CANVAS_HEIGHT_PIXEL = 20;

    QPoint *moveTable;
    int forwardDirect; //1: right 2: down 3: left 4: up
    int speedCounter;

    bool isAlive;
    int **connectedCanvas;

    int query(QPoint p);//get blocktype of p
    bool if_out_of_bound(QPoint p);
    void speed_up();
    void speed_down();


signals:


};

#endif // SNAKE_H
