#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>
#include <queue>
#include <vector>




class snake : public QObject
{
    Q_OBJECT
public:
    snake(int snakeNum, int startLen);
    snake(snake *other);
    void changeDir(int dir);
    void setCanvas(int **canvas);
    void move();
    bool qAlive();
    int snakeN;
    std::queue<QPoint> *snakeNode;
    std::vector<QPair<QPoint, int>> *changedNode;

private:

    static const int CANVAS_WIDTH_PIXEL = 60;
    static const int CANVAS_HEIGHT_PIXEL = 60;

    QPoint *moveTable;

    int forwardDirect; //1: right 2: down 3: left 4: up
    bool isAlive;
    int **connectedCanvas;

    int query(QPoint p);

signals:

};

#endif // SNAKE_H
