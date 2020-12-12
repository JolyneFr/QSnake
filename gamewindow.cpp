#include "gamewindow.h"
#include <string.h>
#include <QDebug>
#include <QMessageBox>

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
        qDebug() << "Failed to load font.";
    }

    setWindowTitle(tr("Enjoy Your Game Here!"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    height_pixel = WINDOW_HEIGHT / pixel;
    width_pixel = WINDOW_WIDTH / pixel;
    savedGames = new std::vector<GameSence*>;
    isContinue = false;
    times = 100;
    timeCounter = 0;


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));


}

void GameWindow::receive_enter_game(int playerNum)
{
    this->show();
    this->PlayerN = playerNum;

    thisGame = new GameSence(PlayerN);
    init_canvas();
    thisGame->setCanvas(canvas);

    thisGame->Snake1->setCanvas(canvas);

    if(thisGame->Snake2)
    {
        thisGame->Snake2->setCanvas(canvas);
    }

    isContinue = true;
    timer->start(times);
}

void GameWindow::init_canvas()
{
    canvas = new int*[width_pixel];
    for(int i = 0; i < width_pixel; i++)
    {
        canvas[i] = new int[height_pixel];
        memset(canvas[i], 0, height_pixel *sizeof(int));
    }

    std::queue<QPoint> *data = thisGame->Snake1->snakeNode;

    for(int i = 0; i < thisGame->startLen; i++)
    {
        QPoint p = data->front();
        data->pop();
        canvas[p.x()][p.y()] = 2;
        data->push(p);
    }

    if (thisGame->Snake2)
    {

        data = thisGame->Snake2->snakeNode;

        for(int i = 0; i < thisGame->startLen; i++)
        {
            QPoint p = data->front();
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
            //qDebug() << "painted orange head!";
            break;
        }
        case 3:
            painter.fillRect(p.x() * pixel, p.y() * pixel, pixel, pixel, tr("red"));
            break;
        }
    }

    thisGame->changedPoint->clear();

    paint_canvas();

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
                case 3:
                    painter.fillRect(x * pixel, y * pixel, pixel, pixel, tr("red"));
                    break;
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
    case Qt::Key_Space:
        isContinue = false;
        break;
    }

    if(!isContinue)
    {
        pause();
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

    thisGame->getChangedSnake();

    timeCounter++;

    if (timeCounter % APPLE_TIME_COUNTER == 1)
    {
        thisGame->getNewApple(this->PlayerN);
        thisGame->Apple->clear();
    }

    if (!thisGame->Snake1->qAlive() || (thisGame->Snake2 && !thisGame->Snake2->qAlive()))
    {
        timer->stop();
        isContinue = false;
        qDebug() << "game end!";
    }

    update();

}

void GameWindow::save_current_game()
{
    GameSence *currentGame = new GameSence(thisGame);
    savedGames->push_back(currentGame);

    QMessageBox::information(NULL, "OH YEAH!", "Game Saved Successfully");


}

void GameWindow::pause()
{
    this->hide();
    emit send_pause();
}

void GameWindow::receive_continue_game()
{
    this->show();
    isContinue = true;
    timer->start(times);
}

void GameWindow::receive_load_game()
{
    load_game(savedGames->size() - 1);
}

void GameWindow::load_game(int gameIndex)
{
    thisGame = (*savedGames)[gameIndex];

    canvas = thisGame->getCanvas();

    update();

    this->show();
    isContinue = true;
    timer->start(times);
}
