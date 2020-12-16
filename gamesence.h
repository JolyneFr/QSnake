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
    /*     number of snakes on canvas     */
    /*     can only be 1 or 2             */
    int playerN;

    /*     true when the snake2 is Delamain     */
    bool ifAuto;

    /*     the pointer to the canvas     */
    /*     stored in gameWindow, gameSence and snakes at the same time*/
    int **gameCanvas;

    static const int CANVAS_WIDTH_PIXEL = 20;
    static const int CANVAS_HEIGHT_PIXEL = 20;

    void init_wall();

    /*     pre-draw snakes on the canvas     */
    void init_snakes(int playerNum, int **canvas);


public:

    static const int SNAKE_START_LEN = 3;

    snake *Snake1;
    snake *Snake2;

    /*     store apples on canvas     */
    /*     to check if apple was eaten     */
    std::vector<QPair<QPoint, int>> *Apple;


    /*     constructors:     */
    /*  1. init constrcut     */
    /*  2. copy constrcut     */
    /*  3. file constrcut     */
    GameSence(int playerNum, bool ifAuto);
    GameSence(GameSence *other);
    GameSence(QString filePath);

    void getNewApple(int);
    void setCanvas(int **canvas);
    void update_apple();
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
