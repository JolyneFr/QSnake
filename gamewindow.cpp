#include "gamewindow.h"
#include <string.h>

void setFontPointSize_game(QWidget *obj, int size)
{
    QFont ft;
    ft.setPointSize(size);
    obj->setFont(ft);
}

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{

    /*     load the font      */

    int fontId = QFontDatabase::addApplicationFont(":/Font/Barrio-Regular.ttf");
    QStringList fontIDs = QFontDatabase::applicationFontFamilies(fontId);
    if (! fontIDs.isEmpty()) {
        QFont font(fontIDs.first());
        QApplication::setFont(font);
    }
    else {
        qDebug()<<"Failed to load font.";
    }

    setWindowTitle(tr("Enjoy Your Game Here!"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    height_pixel = WINDOW_HEIGHT / pixel;
    width_pixel = WINDOW_WIDTH / pixel;
    isContinue = true;

    thisGame = new GameSence(PlayerN);
    init_canvas();
    thisGame->setCanvas(canvas);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));


}

void GameWindow::receive_enter_game(int playerNum)
{
    this->show();
    this->PlayerN = playerNum;
}

void GameWindow::init_canvas()
{
    canvas = new int*[width_pixel];
    for(int i = 0; i < width_pixel; i++)
    {
        canvas[i] = new int[height_pixel];
        memset(canvas[i], 0, height_pixel *sizeof(int));
    }

    for(int i = 0; i < thisGame->startLen; i++)
    {
        std::queue<QPoint> *data = thisGame->Snake1->snakeNode;
        QPoint p = data->front();
        data->pop();
        canvas[p.x()][p.y()] = 2;
        data->push(p);
    }

    if (thisGame->Snake2)
    {
        for(int i = 0; i < thisGame->startLen; i++)
        {
            std::queue<QPoint> *data = thisGame->Snake2->snakeNode;
            QPoint p = data->back();
            data->pop();
            canvas[p.x()][p.y()] = 2;
            data->push(p);
        }
    }

}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QColor snakeColor(tr("orange"));
    QColor wallColor(tr("grey"));
    QColor appleColor(tr("red"));



    for(auto pair_data : *(thisGame->changedPoint))
    {
        QPoint p = pair_data.first;
        int blockType = pair_data.second;
        canvas[p.x()][p.y()] = blockType;

        QPainter painter(this);
        painter.translate(0, WINDOW_HEIGHT - CANVAS_HEIGHT);

        switch(blockType)
        {
        case 0:
        {
            painter.fillRect(p.x() * pixel, p.y() * pixel, pixel, pixel, tr("white"));
            break;
        }
        case 1:
        {
            painter.fillRect(p.x() * pixel, p.y() * pixel, pixel, pixel, tr("grey"));
            break;
        }
        case 2:
        {
            painter.fillRect(p.x() * pixel, p.y() * pixel, pixel, pixel, tr("orange"));
            break;
        }
        }
    }

    thisGame->changedPoint->clear();

    //paint_canvas();


}

void GameWindow::paint_canvas()
{

    QPainter painter(this);
    painter.translate(0, WINDOW_HEIGHT - CANVAS_HEIGHT);

    for(int x = 0; x < width_pixel; x++)
    {
        for(int y = 0; y < height_pixel; y++)
        {
            switch(canvas[x][y])
            {
                case 0:
                {
                    painter.fillRect(x * pixel, y * pixel, pixel, pixel, tr("white"));
                    break;
                }
                case 1:
                {
                    painter.fillRect(x * pixel, y * pixel, pixel, pixel, tr("grey"));
                    break;
                }
                case 2:
                {
                    painter.fillRect(x * pixel, y * pixel, pixel, pixel, tr("orange"));
                    break;
                }
            }
        }
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int snake1Dir = 0;
    int snake2Dir = 0;

    switch(event->key())
    {
    case Qt::Key_Right:
        snake1Dir = 1;break;
    case Qt::Key_Down:
        snake1Dir = 2;break;
    case Qt::Key_Left:
        snake1Dir = 3;break;
    case Qt::Key_Up:
        snake1Dir = 4;break;
    case Qt::Key_D:
        snake2Dir = 1;break;
    case Qt::Key_S:
        snake2Dir = 2;break;
    case Qt::Key_A:
        snake2Dir = 3;break;
    case Qt::Key_W:
        snake2Dir = 4;break;
    }

    thisGame->Snake1->changeDir(snake1Dir);

    if(PlayerN == 2)
    {
        thisGame->Snake2->changeDir(snake2Dir);
    }


}

void GameWindow::timeout()
{
    if(isContinue == false)
    {
        timer->stop();
        return;
    }
    thisGame->Snake1->move();
    if(PlayerN == 2)
    {
        thisGame->Snake2->move();
    }

    update();

    if (!thisGame->Snake1->qAlive() || (thisGame->Snake2 && !thisGame->Snake2->qAlive()))
    {
        timer->stop();
        isContinue = false;

    }

}
