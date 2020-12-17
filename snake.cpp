#include "snake.h"

snake::snake(int snakeNum, int startLen)
{

    snakeN = snakeNum;
    startL = startLen;
    speedCounter = 3;
    isAlive = true;
    lifeN = 1;

    snakeNode = new QQueue<QPoint>;
    overlapNode = new QQueue<QPoint>;

    moveTable = new QPoint[5];
    moveTable[0] = QPoint(0, 0);
    moveTable[1] = QPoint(1, 0);
    moveTable[2] = QPoint(0, 1);
    moveTable[3] = QPoint(-1, 0);
    moveTable[4] = QPoint(0, -1);

}

void snake::init_snake_on_canvas()
{
    if (snakeN == 1)  //snake1 in the left_up corner
    {
        for (int i = 0; i < startL; i++)
        {
            QPoint p(i + 2, 2);
            snakeNode->push_back(p);
            connectedCanvas[p.x()][p.y()] = BlockType::Snake1;
        }
        forwardDirect = 1;

    } else {            //snake2 in the right_down corner

        for (int i = 0; i < startL; i++)
        {
            QPoint p(CANVAS_WIDTH_PIXEL - 3 - i, CANVAS_HEIGHT_PIXEL - 3);
            snakeNode->push_back(p);
            connectedCanvas[p.x()][p.y()] = BlockType::Snake2;
        }
        forwardDirect = 3;

    }
}

snake::snake(snake *other)  //copy construct
{
    snakeN = other->snakeN;
    startL = other->startL;
    speedCounter = other->speedCounter;
    lifeN = other->lifeN;
    snakeNode = new QQueue<QPoint>(*(other->snakeNode));
    overlapNode = new QQueue<QPoint>(*(other->overlapNode));

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

    if (newDir != forwardDirect && (newDir + 1) % 4 != forwardDirect - 1) // only allows 2 directions to change
    {
        forwardDirect = newDir;
    }
}

void snake::move()
{
    BlockType thisType = snakeN == 1 ? Snake1 : Snake2;
    QPoint head = snakeNode->back();
    QPoint rear = snakeNode->front();
    QPoint newHead = head + moveTable[forwardDirect];
    int curBlock = query(newHead);

    bool ifExtend = false;       //if eat the red apple, the snake extend (blocktype = 3)

    switch(curBlock)
    {
    case BlockType::Wall:
    case BlockType::Snake1:
    case BlockType::Snake2:
        lifeN--;
        if (query(newHead) == thisType)
        {
            overlapNode->push_back(newHead);
        }
        if (lifeN == 0 || if_out_of_bound(newHead))
        {
            isAlive = false;
            return;
        }
        break;
    case BlockType::Apple:
        ifExtend = true;
        break;
    case BlockType::LifeFruit:
        lifeN++;  // +1s
        break;
    case BlockType::SpeedUp:
        speed_up();
        break;
    case BlockType::SpeedDown:
        speed_down();
        break;
    case BlockType::BackGround:
        break;
    }

    snakeNode->push_back(newHead);
    connectedCanvas[newHead.x()][newHead.y()] = thisType;


    /*-----Didn't Eat the Red Apple-----*/

    if(!ifExtend)
    {
        snakeNode->pop_front();

        if (!overlapNode->empty() && rear == overlapNode->front())
        {
            overlapNode->pop_front();
        }
        else
        {
            connectedCanvas[rear.x()][rear.y()] = BlockType::BackGround;
        }
    }

}

int snake::getSpeedCounter()
{
    return speedCounter;
}

int snake::getSpeed()
{
    return 6 - speedCounter;
}

void snake::auto_move()
{

    struct PointNode {
        QPoint p;
        PointNode *father;
        PointNode(QPoint _p, PointNode* _f): p(_p), father(_f) {}
    };

    QQueue<PointNode *> bfsQueue;

    bool **visCanvas = new bool*[CANVAS_WIDTH_PIXEL];
    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        visCanvas[i] = new bool[CANVAS_HEIGHT_PIXEL];
        memset(visCanvas[i], 0, CANVAS_HEIGHT_PIXEL *sizeof(bool));
    }

    QPoint head = snakeNode->back();

    bfsQueue.push_back(new PointNode(head, nullptr));
    visCanvas[head.x()][head.y()] = true;

    PointNode *curNode;

    while (!bfsQueue.empty())
    {
        bool isFound = false;
        int size = bfsQueue.size();

        for (int i = 0; i < size; i++)
        {
            curNode = bfsQueue.front();
            if (query(curNode->p) >= BlockType::Apple)
            {
                isFound = true;
                break;
            }

            for (int j = 1; j <= 4; j++)
            {
                QPoint nextP = curNode->p + moveTable[j];

                if ((query(nextP) == BlockType::BackGround || query(nextP) >= BlockType::Apple)
                        && !visCanvas[nextP.x()][nextP.y()])
                {
                    bfsQueue.push_back(new PointNode(nextP, curNode));
                    visCanvas[nextP.x()][nextP.y()] = true;
                }
            }
            bfsQueue.pop_front();
        }
        if (isFound) break;
    }

    for (int i = 0; i < CANVAS_WIDTH_PIXEL; i++)
    {
        delete [] visCanvas[i];
    }
    delete [] visCanvas;

    if (query(curNode->p) >= BlockType::Apple)
    {
        PointNode *back = curNode;
        while (back->father->p != head)
        {
            back = back->father;
        }
        QPoint dir = back->p - head;

        for (int i = 1; i <= 4; i++)
        {
            if (moveTable[i] == dir)
            {
                forwardDirect = i;
                return;
            }
        }
    }
    else
    {
        for (int i = 1; i <= 4; i++)
        {
            QPoint nxt = head + moveTable[i];
            if (connectedCanvas[nxt.x()][nxt.y()] == 0)
            {
                forwardDirect = i;
                return;
            }
        }
    }

}

int snake::query(QPoint p)
{
    return connectedCanvas[p.x()][p.y()];
}

bool &snake::qAlive()
{
    return this->isAlive;
}

bool snake::if_out_of_bound(QPoint p)
{
    return p.x() == 0 || p.y() == 0 || p.x() == CANVAS_WIDTH_PIXEL - 1 || p.y() == CANVAS_HEIGHT_PIXEL - 1;
}

int &snake::direct()
{
    return forwardDirect;
}

QDataStream &operator<<(QDataStream & output, const snake &obj)
{
    output << obj.snakeN << obj.lifeN << obj.forwardDirect << obj.isAlive
           << obj.snakeNode->size() << obj.speedCounter << obj.overlapNode->size();

    for (int i = 0; i < (int)obj.snakeNode->size(); i++)
    {
        QPoint curP = obj.snakeNode->front();
        obj.snakeNode->pop_front();
        output << curP.x() << curP.y();
        obj.snakeNode->push_back(curP);
    }

    for (int i = 0; i < (int)obj.overlapNode->size(); i++)
    {
        QPoint curP = obj.overlapNode->front();
        obj.overlapNode->pop_front();
        output << curP.x() << curP.y();
        obj.overlapNode->push_back(curP);
    }

    return output;
}

QDataStream &operator>>(QDataStream & input, snake &obj)
{
    int snake_length, overlap_length;

    input >> obj.snakeN >> obj.lifeN >> obj.direct() >> obj.qAlive() >> snake_length >> obj.speedCounter >> overlap_length;

    obj.snakeNode->clear();
    obj.overlapNode->clear();

    for (int i = 0; i < snake_length; i++)
    {
        int x, y;
        input >> x >> y;
        obj.snakeNode->push_back(QPoint(x, y));
    }

    for (int i = 0; i < overlap_length; i++)
    {
        int x, y;
        input >> x >> y;
        obj.overlapNode->push_back(QPoint(x, y));
    }

    return input;
}

void snake::speed_up()
{
    if (speedCounter > 1)
        speedCounter--;
}

void snake::speed_down()
{
    if (speedCounter < 5)
        speedCounter++;
}


