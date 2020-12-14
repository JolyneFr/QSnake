#include "gamewindow.h"
#include <QDebug>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("Enjoy Your Game Here!"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    height_pixel = CANVAS_HEIGHT / pixel;
    width_pixel = CANVAS_WIDTH / pixel;
    savedGames = new std::vector<GameSence*>;
    isContinue = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    set_layout();

}

void GameWindow::set_layout()
{
    outerLayout = new QVBoxLayout();

    speedLabel = new QLabel;
    scoreLabel1 = new QLabel;
    lifeLabel1 = new QLabel;
    scoreLabel2 = new QLabel;
    lifeLabel2 = new QLabel;



    QHBoxLayout *topLayout = new QHBoxLayout();

    set_font_point_size(speedLabel, 20);
    set_font_point_size(scoreLabel1, 15);
    set_font_point_size(lifeLabel1, 15);
    set_font_point_size(scoreLabel2, 15);
    set_font_point_size(lifeLabel2, 15);


    topLayout->addWidget(lifeLabel1);
    topLayout->addWidget(scoreLabel1);

    topLayout->addWidget(speedLabel);

    topLayout->addWidget(lifeLabel2);
    topLayout->addWidget(scoreLabel2);

    outerLayout->addLayout(topLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, CANVAS_HEIGHT));

    this->setLayout(outerLayout);
}

void GameWindow::receive_enter_game(int playerNum)
{
    this->show();

    this->PlayerN = playerNum;
    timeCounter = 0;
    thisGame = new GameSence(PlayerN);
    init_canvas();
    thisGame->setCanvas(canvas);

    isContinue = true;

    timer->start(thisGame->times);

    update_labels();
}

void GameWindow::init_canvas()
{
    canvas = new int*[width_pixel];

    // set background

    for(int i = 0; i < width_pixel; i++)
    {
        canvas[i] = new int[height_pixel];
        memset(canvas[i], 0, height_pixel *sizeof(int));
    }

}

void GameWindow::paintEvent(QPaintEvent *event)
{

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
            painter.fillRect(x * pixel, y * pixel, pixel, pixel, colorType[canvas[x][y]]);
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
        on_press_pause();
        break;
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

    timeCounter++;

    if (timeCounter == 1)
    {
        thisGame->getNewApple(this->PlayerN);
    }


    for (QPair<QPoint, int> apple : *(thisGame->Apple))
    {
        QPoint appleP = apple.first;
        int appleT = apple.second;

        if (canvas[appleP.x()][appleP.y()] != appleT)
        {
            thisGame->Apple->clear();
            thisGame->getNewApple(this->PlayerN);

            if (appleT == 5)
            {
                thisGame->speed_up();
                timer->setInterval(thisGame->times);
            }

            if (appleT == 6)
            {
                thisGame->speed_down();
                timer->setInterval(thisGame->times);
            }
        }
    }



    if (!thisGame->Snake1->qAlive() || (PlayerN == 2 && !thisGame->Snake2->qAlive()))
    {
        timer->stop();
        isContinue = false;
        qDebug() << "game end!";
        this->hide();
        emit send_dead();
    }

    update_labels();

    update();

}

void GameWindow::receive_save()
{
    GameSence *currentGame = new GameSence(thisGame);

    savedGames->push_back(currentGame);

    thisGame->save_sence_to_file("./GameSence");

    QMessageBox::information(NULL, "OH YEAH!", "Game Saved Successfully");


}

void GameWindow::on_press_pause()
{
    this->hide();
    emit send_pause();
}

void GameWindow::receive_continue_game()
{
    this->show();
    isContinue = true;
    timer->start(thisGame->times);
}

void GameWindow::receive_load_game()
{

    thisGame = new GameSence("./GameSence");

    canvas = thisGame->getCanvas();

    update();

    this->show();

    isContinue = true;

    timer->start(thisGame->times);
}

void GameWindow::load_game(int gameIndex)
{
    thisGame = new GameSence((*savedGames)[gameIndex]);

    canvas = thisGame->getCanvas();

    update();

    this->show();
    isContinue = true;
    timer->start(thisGame->times);
}

void GameWindow::restart()
{

    savedGames->clear();

    timeCounter = 0;

    thisGame = new GameSence(PlayerN);
    init_canvas();
    thisGame->setCanvas(canvas);

    isContinue = true;

    timer->start(thisGame->times);

    update_labels();


}

void GameWindow::receive_restart()
{
    this->show();
    restart();
}

void GameWindow::update_labels()
{
    speedLabel->setText("SPEED: " + QString::number(thisGame->get_speed()));

    scoreLabel1->setText("Player1: " + QString::number((int)thisGame->Snake1->snakeNode->size() - GameSence::SNAKE_START_LEN));
    lifeLabel1->setText("Life: " + QString::number(thisGame->Snake1->lifeN));

    if (PlayerN == 2)
    {
        scoreLabel2->setText("Player2: " + QString::number((int)thisGame->Snake2->snakeNode->size() - GameSence::SNAKE_START_LEN));
        lifeLabel2->setText("Life: " + QString::number(thisGame->Snake1->lifeN));
    }
    else
    {
        scoreLabel2->setText("Player2: N/A");
        lifeLabel2->setText("Life: N/A");
    }
}

void GameWindow::receive_load_continue()
{


    thisGame = new GameSence("./GameSence");

    canvas = thisGame->getCanvas();

    PlayerN = thisGame->get_playerN();

    update();

    this->show();
    isContinue = true;
    timer->start(thisGame->times);
}



