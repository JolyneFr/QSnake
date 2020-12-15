#ifndef GAMESENCE_H
#define GAMESENCE_H

#include <vector>
#include <QPair>
#include <QPoint>
#include <QObject>
#include <QFile>
#include <QDataStream>
#include "snake.h"

class GameSence: public QObject
{
    Q_OBJECT
private:

    int playerN;
    bool ifAuto;
    int **gameCanvas;

    static const int CANVAS_WIDTH_PIXEL = 30;
    static const int CANVAS_HEIGHT_PIXEL = 30;

    void init_wall();
    void init_snakes(int playerNum, int **canvas);


public:

    static const int SNAKE_START_LEN = 3;

    snake *Snake1;
    snake *Snake2;
    int startLen;
    int times;

    std::vector<QPoint> *Wall;
    std::vector<QPair<QPoint, int>> *Apple;

    GameSence(int playerNum, bool f);
    GameSence(GameSence *other);
    GameSence(QString filePath);
    void getNewApple(int);
    void setCanvas(int **canvas);
    void save_sence_to_file(QString filePath);
    void speed_up();
    void speed_down();
    int get_speed();
    int get_playerN();
    bool get_ifAuto();
    int **getCanvas();

signals:

private slots:


};

#endif // GAMESENCE_H
