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

    /*
     * constructor:
     * init construct -- called when start a new game
     * copy construct -- called when load game sence
     */
    snake(int snakeNum, int startLen);
    snake(snake *other);

    void changeDir(int dir);
    void setCanvas(int **canvas);

    /*
     * move:
     * get newHead by forwardDir, and query it on canvas
     * act according to brick-type of canvas[newHead]
     * deal with apple here
     */
    void move();

    /*
     * auto_move:
     * using BFS algorithm to find shortest road to shortest apple
     * just change director, do not move the head
     * so still need to call move() before this func
     */
    void auto_move();

    void init_snake_on_canvas();
    int getSpeedCounter();
    int getSpeed();
    int &direct();
    bool &qAlive();     //query if alive
    int snakeN;        //nth snake (1 or 2)
    int startL;
    int lifeN;         //number of life

    /*
     * snakeNode: store all points of this snake
     * overlapNode: to deal with skip-hazard, store all overlap snake points here
     */
    QQueue<QPoint> *snakeNode;
    QQueue<QPoint> *overlapNode;

    /*
     * friend functions for file storing & loading
     * using QDataStream to simplify codes
     */
    friend QDataStream &operator<<(QDataStream &, const snake &);
    friend QDataStream &operator>>(QDataStream &, snake &);

private:

    /*
     * for cross_the_bound checking
     * DO NOT CHANGE
     */
    static const int CANVAS_WIDTH_PIXEL = 30;
    static const int CANVAS_HEIGHT_PIXEL = 30;

    QPoint *moveTable; // get move vector by index below
    int forwardDirect; // 1: right 2: down 3: left 4: up
    int speedCounter;  // range from 1 to 5 (slow to fast)

    bool isAlive;
    int **connectedCanvas;

    int query(QPoint p);//get blocktype of p
    bool if_out_of_bound(QPoint p);  // can't cross the bound in this game

    /*
     * adjust snake speed here
     */
    void speed_up();
    void speed_down();


signals:


};

#endif // SNAKE_H
