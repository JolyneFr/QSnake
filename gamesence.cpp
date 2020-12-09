#include "gamesence.h"

GameSence::GameSence(int playerNum)
{
    playerN = playerNum;
    init_wall();
    init_snakes(playerNum);
    changedPoint = new std::vector<QPair<QPoint, int>>;
    startLen = SNAKE_START_LEN;
}

void GameSence::setCanvas(int **canvas)
{
    gameCanvas = canvas;
}

void GameSence::init_wall()
{
    Wall = new std::vector<QPoint>;

    for (int i = 0; i < CANVAS_HEIGHT_PIXEL; i++)
    {
        Wall->push_back(QPoint(0, i));
        Wall->push_back(QPoint(CANVAS_WIDTH_PIXEL - 1, i));
    }

    for (int i = 1; i < CANVAS_WIDTH_PIXEL - 1; i++)
    {
        Wall->push_back(QPoint(i, 0));
        Wall->push_back(QPoint(i, CANVAS_HEIGHT_PIXEL - 1));
    }
}

void GameSence::init_snakes(int playerNum)
{

    Snake1 = new snake(1, SNAKE_START_LEN);

    if (playerN == 2)
    {
        Snake2 = new snake(2, SNAKE_START_LEN);
    }
    else
    {
        Snake2 = nullptr;
    }

}

void GameSence::getChangedSnake()
{
    auto data = Snake1->changedNode;
    changedPoint->insert(changedPoint->end(), data->begin(), data->end());

    if(Snake2)
    {
        data = Snake2->changedNode;
        changedPoint->insert(changedPoint->end(), data->begin(), data->end());
    }
}
