#include "gamewindow.h"
#include <QDebug>
#include <QMessageBox>

QString BlockName[9] = {"BackGround", "Wall", "Snake1", "Snake2", "Apple", "LifeFruit", "SpeedUp", "SpeedDown", "Exchange"};

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
    outerLayout = new QHBoxLayout();

    speedLabel1 = new QLabel;
    speedLabel2 = new QLabel;
    scoreLabel1 = new QLabel;
    lifeLabel1 = new QLabel;
    scoreLabel2 = new QLabel;
    lifeLabel2 = new QLabel;

    QVBoxLayout *leftLayout = new QVBoxLayout();

    scoreLabel1->setStyleSheet("color:orange");
    scoreLabel2->setStyleSheet("color:navy");


    QVBoxLayout *topLayout = new QVBoxLayout();
    QHBoxLayout *player1 = new QHBoxLayout();
    QHBoxLayout *player2 = new QHBoxLayout();

    set_font_point_size(speedLabel1, 20);
    set_font_point_size(speedLabel2, 20);
    set_font_point_size(scoreLabel1, 20);
    set_font_point_size(lifeLabel1, 20);
    set_font_point_size(scoreLabel2, 20);
    set_font_point_size(lifeLabel2, 20);


    player1->addWidget(lifeLabel1);
    player1->addWidget(scoreLabel1);
    player1->addWidget(speedLabel1);

    player2->addWidget(lifeLabel2);
    player2->addWidget(scoreLabel2);
    player2->addWidget(speedLabel2);

    topLayout->addLayout(player1);
    topLayout->addLayout(player2);
    leftLayout->addLayout(topLayout);
    leftLayout->addSpacerItem(new QSpacerItem(CANVAS_WIDTH, CANVAS_HEIGHT));

    outerLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    for (int i = 1; i < 9; i++)
    {
        QLabel *color = new QLabel;
        color->setText(BlockName[i]);
        set_font_point_size(color, 20);
        color->setStyleSheet("color:" + colorType[i]);
        rightLayout->addWidget(color);
    }

    outerLayout->addLayout(rightLayout);

    this->setLayout(outerLayout);
}

void GameWindow::receive_enter_game(int playerNum, int **carriedCanvas)
{
    this->show();

    timeCounter = 0;
    PlayerN = (playerNum - 1) % 2 + 1;
    bool ifAuto = (playerNum - 1) / 2;
    thisGame = new GameSence(PlayerN, ifAuto);

    if (carriedCanvas)
    {
        defaultCanvas = carriedCanvas;
        canvas = get_canvas_clone(carriedCanvas);
        thisGame->setCanvas(canvas);
    }
    else
    {
        defaultCanvas = nullptr;
        init_canvas();
        thisGame->setCanvas(canvas);
    }

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

    move_snake(1);
    if (thisGame->get_playerN() == 2)
    {
        move_snake(2);
    }

    update_apples();

    check_death();

    update_labels();

    update();

}

void GameWindow::check_death()
{
    int deathNum = 0;
    if (!thisGame->Snake1->qAlive())
    {
        deathNum = 1;
    }

    if (thisGame->get_playerN() == 2 && !thisGame->Snake2->qAlive())
    {
        deathNum = 2;
    }

    if (deathNum)
    {
        timer->stop();
        isContinue = false;

        this->hide();
        emit send_dead(deathNum, thisGame->get_playerN(), thisGame->get_ifAuto());
    }
}

void GameWindow::update_apples()
{
    for (auto apple = thisGame->Apple->begin();
              apple != thisGame->Apple->end();
              apple++)
    {
        QPoint appleP = apple->first;
        int appleT = apple->second;

        if (canvas[appleP.x()][appleP.y()] != appleT)
        {
            thisGame->Apple->erase(apple);
            thisGame->getNewApple(1);
            if (appleT == BlockType::Exchange && thisGame->get_playerN() == 2)
            {
                exchange_snakes();
            }
        }
    }
}

void GameWindow::exchange_snakes()
{
    snake * tmp = thisGame->Snake1;
    thisGame->Snake1 = thisGame->Snake2;
    thisGame->Snake1->snakeN = 1;
    thisGame->Snake2 = tmp;
    thisGame->Snake2->snakeN = 2;


}

void GameWindow::move_snake(int N)
{
    snake *curSnake = (N == 1) ? thisGame->Snake1 : thisGame->Snake2;

    if (timeCounter % curSnake->getSpeedCounter() == 0)
    {
        if (thisGame->get_ifAuto() && thisGame->get_playerN() == N)
        {
            curSnake->auto_move();
        }
        curSnake->move();
    }

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
    emit send_pause(canvas);
}

void GameWindow::receive_continue_game(int **newCanvas)
{
    this->show();
    isContinue = true;
    timer->start(times);
}

void GameWindow::receive_load_game()
{

    QFile file("./GameSence");

    if (!file.exists() || file.size() < 10)
    {
        QMessageBox::information(NULL, "OH NO!", "No Game Saved.\n Please save a game before load.");
        emit send_back_to_menu();
        return;
    }

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

int** GameWindow::get_canvas_clone(int **defaultCanvas)
{
    if (!defaultCanvas)
    {
        return nullptr;
    }

    int **cloneCanvas = new int*[width_pixel];

    for(int i = 0; i < width_pixel; i++)
    {
        cloneCanvas[i] = new int[height_pixel];
        for (int j = 0; j < height_pixel; j++)
        {
            cloneCanvas[i][j] = defaultCanvas[i][j];
        }
    }
    return cloneCanvas;
}

void GameWindow::restart()
{

    savedGames->clear();

    timeCounter = 0;

    bool ifAuto = thisGame->get_ifAuto();

    thisGame = new GameSence(PlayerN, ifAuto);

    if (defaultCanvas)
    {
        int **cloneCanvas = get_canvas_clone(defaultCanvas);
        canvas = cloneCanvas;
        thisGame->setCanvas(cloneCanvas);
    }
    else
    {
        init_canvas();
        thisGame->setCanvas(canvas);
    }

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
    speedLabel1->setText("SPEED: " + QString::number((int)thisGame->Snake1->getSpeed()));
    scoreLabel1->setText("Player1: " + QString::number((int)thisGame->Snake1->snakeNode->size() - GameSence::SNAKE_START_LEN));
    lifeLabel1->setText("Life: " + QString::number(thisGame->Snake1->lifeN));

    if (thisGame->get_playerN() == 2)
    {
        speedLabel2->setText("SPEED: " + QString::number((int)thisGame->Snake2->getSpeed()));
        scoreLabel2->setText("Player2: " + QString::number((int)thisGame->Snake2->snakeNode->size() - GameSence::SNAKE_START_LEN));
        lifeLabel2->setText("Life: " + QString::number(thisGame->Snake1->lifeN));
    }
    else
    {
        speedLabel2->setText("SPEED: N/A");
        scoreLabel2->setText("Player2: N/A");
        lifeLabel2->setText("Life: N/A");
    }
}

void GameWindow::receive_load_continue()
{

    QFile file("./GameSence");

    if (!file.exists())
    {
        QMessageBox::information(NULL, "OH NO!", "No Game Saved.\n Please save a game before load.");
        emit send_back_to_menu();
        return;
    }


    thisGame = new GameSence("./GameSence");

    canvas = thisGame->getCanvas();

    PlayerN = thisGame->get_playerN();

    update();

    this->show();
    isContinue = true;
    timer->start(times);
}



