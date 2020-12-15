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

    timeCounter = 0;
    switch (playerNum) {
    case 1:
    case 2:
        thisGame = new GameSence(playerNum, false);
        this->PlayerN = playerNum;
        break;
    case 3:
        thisGame = new GameSence(2, true);
        this->PlayerN = 2;
        break;
    }
    init_canvas();
    thisGame->setCanvas(canvas);

    isContinue = true;

    timer->start(times);

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

    if(thisGame->get_playerN() == 2 && !thisGame->get_ifAuto())
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

    timeCounter++;

    if (timeCounter == 1)
    {
        thisGame->getNewApple(this->PlayerN);
    }

    if (timeCounter % (thisGame->Snake1->getSpeedCounter()) == 0)
    {
        thisGame->Snake1->move();
    }

    if(thisGame->get_playerN() == 2 && timeCounter % (thisGame->Snake2->getSpeedCounter()) == 0)
    {
        if (thisGame->get_ifAuto())
        {
            thisGame->Snake2->auto_move();
        }
        thisGame->Snake2->move();
    }


    for (QPair<QPoint, int> apple : *(thisGame->Apple))
    {
        QPoint appleP = apple.first;
        int appleT = apple.second;

        if (canvas[appleP.x()][appleP.y()] != appleT)
        {
            thisGame->Apple->clear();
            thisGame->getNewApple(this->PlayerN);
        }
    }

    if (!thisGame->Snake1->qAlive() || (thisGame->get_playerN() == 2 && !thisGame->Snake2->qAlive()))
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
    timer->start(times);
}

void GameWindow::receive_load_game()
{

    thisGame = new GameSence("./GameSence");

    canvas = thisGame->getCanvas();

    update();

    this->show();

    isContinue = true;

    timer->start(times);
}

void GameWindow::load_game(int gameIndex)
{
    thisGame = new GameSence((*savedGames)[gameIndex]);

    canvas = thisGame->getCanvas();

    update();

    this->show();
    isContinue = true;
    timer->start(times);
}

void GameWindow::restart()
{

    savedGames->clear();

    timeCounter = 0;

    bool ifAuto = thisGame->get_ifAuto();

    thisGame = new GameSence(PlayerN, ifAuto);
    init_canvas();
    thisGame->setCanvas(canvas);

    isContinue = true;

    timer->start(times);

    update_labels();


}

void GameWindow::receive_restart()
{
    this->show();
    restart();
}

void GameWindow::update_labels()
{
    speedLabel->setText("SPEED: ");

    scoreLabel1->setText("Player1: " + QString::number((int)thisGame->Snake1->snakeNode->size() - GameSence::SNAKE_START_LEN));
    lifeLabel1->setText("Life: " + QString::number(thisGame->Snake1->lifeN));

    if (thisGame->get_playerN() == 2)
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
    timer->start(times);
}



