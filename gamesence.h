#ifndef GAMESENCE_H
#define GAMESENCE_H

#include <vector>
#include <QPair>
#include <QPoint>
#include <QObject>
#include "snake.h"

class GameSence: public QObject
{
    Q_OBJECT
private:

    int playerN;
    int **gameCanvas;

    static const int CANVAS_WIDTH_PIXEL = 60;
    static const int CANVAS_HEIGHT_PIXEL = 60;
    static const int SNAKE_START_LEN = 3;

    void init_wall();
    void init_snakes(int playerNum);


public:

    snake *Snake1;
    snake *Snake2;
    int startLen;

    std::vector<QPoint> *Wall;
    std::vector<QPair<QPoint, int>> *Apple;

    std::vector<QPair<QPoint, int>> *changedPoint;

    GameSence(int playerNum);
    GameSence(GameSence *other);
    void getChangedSnake();
    void getNewApple(int);
    void setCanvas(int **canvas);
    int **getCanvas();

signals:

private slots:


};

#endif // GAMESENCE_H
