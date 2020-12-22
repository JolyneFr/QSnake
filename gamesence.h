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
    /*
     * number of snakes on canvas
     * can only be 1 or 2
     * init when constructed
     */
    int playerN;

    /*
     * true when this game includes Delamain
     * init when constructed
     */
    bool ifAuto;

    /*
     * the pointer to the canvas
     * stored in gameWindow, gameSence and snakes at the same time
     */
    int **gameCanvas;

    /*
     * abstruct size of game canvas
     * DO NOT change without thinking
     * equals to CANVAS_WIDTH / pixel & CANVAS_HEIGHT / pixel
     */
    static const int CANVAS_WIDTH_PIXEL = 20;
    static const int CANVAS_HEIGHT_PIXEL = 20;

    void init_wall();

    /*
     * pre-draw snakes on the canvas
     * since the canvas won't draw snake's body whlie playing
     */
    void init_snakes(int playerNum, int **canvas);


public:

    /*
     * init length of snake
     * free to change (below CANVAS_WIDTH_PIXEL)
     */
    static const int SNAKE_START_LEN = 3;

    snake *Snake1;
    snake *Snake2;

    /*
     * store apples on canvas
     * to check whether apple was eaten
     */
    std::vector<QPair<QPoint, int>> *Apple;


    /*  constructors:
     *  1. init constrcut -- called when start a new game
     *  2. copy constrcut -- called when save game / load game from another GameSence
     *  3. file constrcut -- called when load game from file
     */
    GameSence(int playerNum, bool ifAuto);
    GameSence(GameSence *other);
    GameSence(QString filePath);

    /*
     * generate new apple on the canvas
     * adjust rates of apples here
     */
    void getNewApple(int appleNum);

    /*
     * set new gameCanvas to this GameSence & its snakes
     * called when you want to change it
     */
    void setCanvas(int **canvas);

    /*
     * update Apple vector by scanning all canvas
     * use AFTER setting new canvas
     */
    void update_apple();

    void save_sence_to_file(QString filePath);

    /*
     * functions which returns private members
     */
    int get_playerN();
    bool get_ifAuto();
    int **getCanvas();


};

#endif // GAMESENCE_H
