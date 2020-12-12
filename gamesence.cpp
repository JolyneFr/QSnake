#include "gamesence.h"
#include <ctime>

GameSence::GameSence(int playerNum)
{

    changedPoint = new std::vector<QPair<QPoint, int>>;
    Apple = new std::vector<QPair<QPoint, int>>;

    playerN = playerNum;
    init_wall();
    init_snakes(playerNum);
    startLen = SNAKE_START_LEN;
}

GameSence::GameSence(GameSence *other)
{
    playerN = other->playerN;
    startLen = other->startLen;
    Wall = new std::vector<QPoint>(*(other->Wall));
    changedPoint = new std::vector<QPair<QPoint, int>>(*(other->changedPoint));;
    Apple = new std::vector<QPair<QPoint, int>>(*(other->Apple));

    gameCanvas = new int*[CANVAS_WIDTH_PIXEL];
    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        gameCanvas[i] = new int[CANVAS_HEIGHT_PIXEL];

        for (int j = 0; j < CANVAS_HEIGHT_PIXEL; j++)
        {
            gameCanvas[i][j] = other->gameCanvas[i][j];
        }

    }

    Snake1 = new snake(other->Snake1);
    Snake1->setCanvas(gameCanvas);

    if(playerN == 2)
    {
        Snake2 = new snake(other->Snake2);
        Snake2->setCanvas(gameCanvas);
    }
    else
    {
        Snake2 = nullptr;
    }

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
        changedPoint->push_back(QPair<QPoint, int>(QPoint(0, i), 1));
        changedPoint->push_back(QPair<QPoint, int>(QPoint(CANVAS_WIDTH_PIXEL - 1, i), 1));
    }

    for (int i = 1; i < CANVAS_WIDTH_PIXEL - 1; i++)
    {
        Wall->push_back(QPoint(i, 0));
        Wall->push_back(QPoint(i, CANVAS_HEIGHT_PIXEL - 1));
        changedPoint->push_back(QPair<QPoint, int>(QPoint(i, 0), 1));
        changedPoint->push_back(QPair<QPoint, int>(QPoint(i, CANVAS_HEIGHT_PIXEL - 1), 1));
    }
}

void GameSence::init_snakes(int playerNum)
{

    Snake1 = new snake(1, SNAKE_START_LEN);

    if (playerNum == 2)
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
    data->clear();

    if(Snake2)
    {
        data = Snake2->changedNode;
        changedPoint->insert(changedPoint->end(), data->begin(), data->end());
    }
    data->clear();
}

void GameSence::getNewApple(int Num)
{
    srand(time(NULL));

    while (Num > 0)
    {
        int x = rand() % (CANVAS_WIDTH_PIXEL - 3) + 2;
        int y = rand() % (CANVAS_HEIGHT_PIXEL - 3) + 2;
        int type = 3;

        if (gameCanvas[x][y] == 0)
        {
            Apple->push_back(QPair<QPoint, int>(QPoint(x, y), type));
            changedPoint->push_back(QPair<QPoint, int>(QPoint(x, y), type));
            Num--;
        }

    }
}

int** GameSence::getCanvas()
{
    return gameCanvas;
}
