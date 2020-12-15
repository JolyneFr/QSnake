#include "gamesence.h"
#include <ctime>
#include <QDebug>

GameSence::GameSence(int playerNum, bool f)
{

    Apple = new std::vector<QPair<QPoint, int>>;

    playerN = playerNum;
    ifAuto = f;
    times = 100;
    startLen = SNAKE_START_LEN;
}

GameSence::GameSence(GameSence *other)
{
    playerN = other->playerN;
    startLen = other->startLen;
    times = other->times;
    ifAuto = other->ifAuto;
    Wall = new std::vector<QPoint>(*(other->Wall));
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

GameSence::GameSence(QString filePath)
{
    QFile file(filePath);

    file.open(QIODevice::ReadOnly);

    if (file.exists())
    {
        qDebug() << "start to load.";
    }

    QDataStream input(&file);

    input >> playerN >> startLen >> times >> ifAuto;

    std::vector<QPoint>::size_type wall_size;
    std::vector<QPair<QPoint, int>>::size_type apple_size;

    input >> wall_size >> apple_size;

    gameCanvas = new int*[CANVAS_WIDTH_PIXEL];

    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        gameCanvas[i] = new int[CANVAS_HEIGHT_PIXEL];

        for (int j = 0; j < CANVAS_HEIGHT_PIXEL; j++)
        {
            input >> gameCanvas[i][j];
        }

    }

    Wall = new std::vector<QPoint>;

    for (int i = 0; i < (int)wall_size; i++)
    {
        int x, y;
        input >> x >> y;
        Wall->push_back(QPoint(x, y));
    }

    Apple = new std::vector<QPair<QPoint, int>>;

    for (int i = 0; i < (int)apple_size; i++)
    {
        int x, y, type;
        input >> x >> y >> type;
        Apple->push_back(QPair<QPoint, int>(QPoint(x, y), type));
    }

    Snake1 = new snake(0, 0);
    input >> *Snake1;
    Snake1->setCanvas(gameCanvas);

    if (playerN == 2)
    {
        Snake2 = new snake(0, 0);
        input >> *Snake2;
        Snake2->setCanvas(gameCanvas);
    }



}

void GameSence::setCanvas(int **canvas)
{
    gameCanvas = canvas;
    init_snakes(playerN, canvas);
    init_wall();
}

void GameSence::init_wall()
{
    Wall = new std::vector<QPoint>;

    for (int i = 0; i < CANVAS_HEIGHT_PIXEL; i++)
    {
        Wall->push_back(QPoint(0, i));
        Wall->push_back(QPoint(CANVAS_WIDTH_PIXEL - 1, i));
        gameCanvas[0][i] = 1;
        gameCanvas[CANVAS_WIDTH_PIXEL - 1][i] = 1;
    }

    for (int i = 1; i < CANVAS_WIDTH_PIXEL - 1; i++)
    {
        Wall->push_back(QPoint(i, 0));
        Wall->push_back(QPoint(i, CANVAS_HEIGHT_PIXEL - 1));
        gameCanvas[i][0] = 1;
        gameCanvas[i][CANVAS_HEIGHT_PIXEL - 1] = 1;
    }
}

void GameSence::init_snakes(int playerNum, int **canvas)
{

    Snake1 = new snake(1, SNAKE_START_LEN);
    Snake1->setCanvas(canvas);
    Snake1->init_snake_on_canvas();

    if (playerNum == 2)
    {
        Snake2 = new snake(2, SNAKE_START_LEN);
        Snake2->setCanvas(canvas);
        Snake2->init_snake_on_canvas();
    }
    else
    {
        Snake2 = nullptr;
    }

}

bool GameSence::get_ifAuto()
{
    return ifAuto;
}

void GameSence::getNewApple(int Num)
{
    srand(time(NULL));

    while (Num > 0)
    {
        int x = rand() % (CANVAS_WIDTH_PIXEL - 3) + 2;
        int y = rand() % (CANVAS_HEIGHT_PIXEL - 3) + 2;
        int typerand = rand() % 20;
        int type;

        if(typerand < 13)
        {
            type = 3;
        }
        else if(typerand < 15)
        {
            type = 4;
        }
        else if(typerand < 17)
        {
            type = 5;
        }
        else
        {
            type = 6;
        }

        if (gameCanvas[x][y] == 0)
        {
            Apple->push_back(QPair<QPoint, int>(QPoint(x, y), type));
            gameCanvas[x][y] = type;
            Num--;
        }

    }
}

int** GameSence::getCanvas()
{
    return gameCanvas;
}

void GameSence::speed_up()
{
    if (times > 50)
        times -= 25;
}

void GameSence::speed_down()
{
    if (times < 150)
        times += 25;
}

int GameSence::get_speed()
{
    return (175 - times) / 25;
}

void GameSence::save_sence_to_file(QString filePath)
{
    QFile file(filePath);

    file.open(QIODevice::WriteOnly);

    if (file.exists())
    {
        qDebug() << "start to save.";
    }

    QDataStream output(&file);

    output << playerN << startLen << times << ifAuto;

    output << Wall->size() << Apple->size();

    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        for (int j = 0; j < CANVAS_HEIGHT_PIXEL; j++)
        {
            output << gameCanvas[i][j];
        }
    }

    for (QPoint p : *Wall)
    {
        output << p.x() << p.y();
    }

    for (auto apple : *Apple)
    {
        QPoint appleP = apple.first;
        int appleT = apple.second;
        output << appleP.x() << appleP.y() << appleT;
    }

    output << *Snake1;

    if (playerN == 2)
    {
        output << *Snake2;
    }

    file.close();
}

int GameSence::get_playerN()
{
    return playerN;
}



