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

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 8));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("Select Game Mode!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    set_font_point_size(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

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

    buttons->addWidget(singlePlayer);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 40));
    buttons->addWidget(multiPlayer);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

    QHBoxLayout *backLayout = new QHBoxLayout();
    backLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5 * 4, 1));
    myButton * backButton = new myButton();
    backButton->setText(tr("Back"));
    connect(backButton, &QPushButton::clicked, this, &SelectWindow::on_click_back);
    backLayout->addWidget(backButton);
    outerLayout->addLayout(backLayout);

    this->setLayout(outerLayout);
}

void SelectWindow::on_click_back()
{
    this->hide();
    emit send_back();
}

void SelectWindow::on_click_singleplayer()
{
    this->hide();
    emit send_enter(1);
}

void SelectWindow::on_click_multiplayer()
{
    this->hide();
    emit send_enter(2);
}

void SelectWindow::receive_start()
{
    this->show();
}


