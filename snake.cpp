#include "snake.h"

snake::snake(int snakeNum, int startLen)
{

    snakeN = snakeNum;
    isAlive = true;

    snakeNode = new std::queue<QPoint>;
    changedNode = new std::vector<QPair<QPoint, int>>;

    moveTable = new QPoint[5];
    moveTable[0] = QPoint(0, 0);
    moveTable[1] = QPoint(1, 0);
    moveTable[2] = QPoint(0, 1);
    moveTable[3] = QPoint(-1, 0);
    moveTable[4] = QPoint(0, -1);

    if (snakeNum == 1)
    {

        for (int i = 0; i < startLen; i++)
        {
            snakeNode->push(QPoint(i + 2, 2));
        }
        forwardDirect = 1;

    } else {

        for (int i = 0; i < startLen; i++)
        {
            snakeNode->push(QPoint(CANVAS_WIDTH_PIXEL - 2 - i, CANVAS_HEIGHT_PIXEL - 3));
        }
        forwardDirect = 3;

    }

}

snake::snake(snake *other)
{
    snakeN = other->snakeN;
    snakeNode = new std::queue<QPoint>(*(other->snakeNode));
    changedNode = new std::vector<QPair<QPoint, int>>(*(other->changedNode));

    moveTable = other->moveTable;
    forwardDirect = other->forwardDirect;
    isAlive = other->isAlive;
}

void snake::setCanvas(int **canvas)
{
    connectedCanvas = canvas;
}

void snake::changeDir(int newDir)
{

    if (newDir == 0) return;

    if (newDir != forwardDirect && (newDir + 1) % 4 != forwardDirect - 1)
    {
        forwardDirect = newDir;
    }
}

void snake::move()
{
    QPoint head = snakeNode->back();
    QPoint rear = snakeNode->front();
    QPoint newHead = head + moveTable[forwardDirect];
    int blockType = query(newHead);

    int ifExtend = false;

    switch(blockType)
    {
    case 1:
    case 2:
        isAlive = false;
        return;
    case 3:
        ifExtend = true;
        break;
    case 0:
        break;
    }

    snakeNode->push(newHead);
    changedNode->push_back(QPair<QPoint, int>(newHead, 2));

    if(!ifExtend)
    {
        snakeNode->pop();
        changedNode->push_back(QPair<QPoint, int>(rear, 0));
    }


}

int snake::query(QPoint p)
{
    return connectedCanvas[p.x()][p.y()];
}

bool snake::qAlive()
{
    return this->isAlive;
}

