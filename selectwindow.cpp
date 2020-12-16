#include "selectwindow.h"
#include "functions.h"

SelectWindow::SelectWindow(QWidget *parent) : QDialog(parent)
{


    setWindowTitle(tr("Select Your Game Mode"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    set_layout();
}

void SelectWindow::set_layout()
{
    QVBoxLayout *outerLayout = new QVBoxLayout();

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 15));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("Select Game Mode!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    set_font_point_size(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 20));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * singlePlayer = new myButton();
    singlePlayer->setText(tr("SinglePlayer"));
    singlePlayer->resize(300, 100);
    connect(singlePlayer, &QPushButton::clicked, this, &SelectWindow::on_click_singleplayer);

    myButton * multiPlayer = new myButton();
    multiPlayer->setText(tr("MultiPlayer"));
    multiPlayer->resize(300, 100);
    connect(multiPlayer, &QPushButton::clicked, this, &SelectWindow::on_click_multiplayer);

    myButton * aiShow = new myButton();
    aiShow->setText(tr("Just Show Delamain"));
    aiShow->resize(300, 100);
    connect(aiShow, &QPushButton::clicked, this, &SelectWindow::on_click_aishow);

    myButton * aiFight = new myButton();
    aiFight->setText(tr("Fight with Delamain!"));
    aiFight->resize(300, 100);
    connect(aiFight, &QPushButton::clicked, this, &SelectWindow::on_click_aifight);

    buttons->addWidget(singlePlayer);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(multiPlayer);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(aiShow);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(aiFight);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 15));

    QHBoxLayout *backLayout = new QHBoxLayout();
    backLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5 * 4, 1));
    myButton * backButton = new myButton();
    backButton->setText(tr("Back"));
    connect(backButton, &QPushButton::clicked, this, &SelectWindow::on_click_back);
    backLayout->addWidget(backButton);
    outerLayout->addLayout(backLayout);

    this->setLayout(outerLayout);
}

int** SelectWindow::get_canvas_clone()
{
    if (!carriedCanvas)
    {
        return nullptr;
    }

    int **canvas = new int*[width_pixel];

    for(int i = 0; i < width_pixel; i++)
    {
        canvas[i] = new int[height_pixel];
        for (int j = 0; j < height_pixel; j++)
        {
            canvas[i][j] = carriedCanvas[i][j];
        }
    }
    return canvas;
}

void SelectWindow::on_click_back()
{
    this->hide();
    emit send_back();
}

void SelectWindow::on_click_singleplayer()
{
    this->hide();
    emit send_enter(1, get_canvas_clone());
}

void SelectWindow::on_click_multiplayer()
{
    this->hide();
    emit send_enter(2, get_canvas_clone());
}

void SelectWindow::on_click_aishow()
{
    this->hide();
    emit send_enter(3, get_canvas_clone());
}

void SelectWindow::on_click_aifight()
{
    this->hide();
    emit send_enter(4, get_canvas_clone());
}

void SelectWindow::receive_start(int **canvas)
{
    carriedCanvas = canvas;
    this->show();
}


