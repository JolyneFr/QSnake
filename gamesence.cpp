#include "gamesence.h"
#include <ctime>
#include <QDebug>

GameSence::GameSence(int playerNum, bool f)
{
    Apple = new std::vector<QPair<QPoint, int>>;

    playerN = playerNum;
    ifAuto = f;
}

GameSence::GameSence(GameSence *other)
{
    playerN = other->playerN;
    ifAuto = other->ifAuto;
    Apple = new std::vector<QPair<QPoint, int>>(*(other->Apple)); // copy ELEMENTS

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

    if (!file.exists())
    {
        qDebug() << "File didn't exist. Please save a game before load.";
        return;
    }

    QDataStream input(&file);

    input >> playerN >> ifAuto;

    std::vector<QPair<QPoint, int>>::size_type apple_size;

    input >> apple_size;

    gameCanvas = new int*[CANVAS_WIDTH_PIXEL];

    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        gameCanvas[i] = new int[CANVAS_HEIGHT_PIXEL];

        for (int j = 0; j < CANVAS_HEIGHT_PIXEL; j++)
        {
            input >> gameCanvas[i][j];
        }

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
    else
    {
        Snake2 = nullptr;
    }



}

void GameSence::setCanvas(int **canvas)
{
    gameCanvas = canvas;
    init_snakes(playerN, canvas);
    init_wall();
    update_apple();
}

void GameSence::update_apple()
{
    Apple->clear();

    for (int i = 1; i < CANVAS_WIDTH_PIXEL - 1; i++)
    {
        for (int j = 1; j < CANVAS_HEIGHT_PIXEL - 1; j++)
        {
            if (gameCanvas[i][j] >= BlockType::Apple)
            {
                Apple->push_back(QPair<QPoint, int>(QPoint(i, j), gameCanvas[i][j]));
            }
        }
    }
}

void GameSence::init_wall()
{
    for (int i = 0; i < CANVAS_HEIGHT_PIXEL; i++)
    {
        gameCanvas[0][i] = BlockType::Wall;
        gameCanvas[CANVAS_WIDTH_PIXEL - 1][i] = BlockType::Wall;
    }

    for (int i = 1; i < CANVAS_WIDTH_PIXEL - 1; i++)
    {
        gameCanvas[i][0] = BlockType::Wall;
        gameCanvas[i][CANVAS_HEIGHT_PIXEL - 1] = BlockType::Wall;
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
            type = BlockType::Apple;
        }
        else if(typerand < 15)
        {
            type = BlockType::LifeFruit;
        }
        else if(typerand < 18)
        {
            type = BlockType::SpeedUp;
        }
        else
        {
            type = BlockType::SpeedDown;
        }

        if (typerand < 2 && playerN == 2)
        {
            type = BlockType::Exchange;
        }

        if (gameCanvas[x][y] == BlockType::BackGround)
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

void GameSence::save_sence_to_file(QString filePath)
{
    QFile file(filePath);

    file.open(QIODevice::WriteOnly);

    if (file.exists())
    {
        qDebug() << "start to save.";
    }

    QDataStream output(&file);

    output << playerN << ifAuto;

    output << Apple->size();

    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        for (int j = 0; j < CANVAS_HEIGHT_PIXEL; j++)
        {
            output << gameCanvas[i][j];
        }
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



