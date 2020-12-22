#include "deadwindow.h"
#include "functions.h"

DeadWindow::DeadWindow(QWidget *parent) : QDialog(parent)
{

    setWindowTitle(tr("You Didn't Survive."));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    set_layout();
}

void DeadWindow::set_layout()
{

    setStyleSheet("background-color: seashell");

    QVBoxLayout *outerLayout = new QVBoxLayout();

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 8));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    start = new QLabel("Dead? You Idiot!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    set_font_point_size(start, 50);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 40));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * restartButton = new myButton();
    restartButton->setText(tr("Restart"));
    connect(restartButton, &QPushButton::clicked, this, &DeadWindow::on_click_restart);

    myButton * loadButton = new myButton();
    loadButton->setText("Load Game");
    connect(loadButton, &QPushButton::clicked, this, &DeadWindow::on_click_load);

    myButton * backButton = new myButton();
    backButton->setText(tr("Back to Menu"));
    connect(backButton, &QPushButton::clicked, this, &DeadWindow::on_click_back);

    buttons->addWidget(restartButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(loadButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(backButton);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

    this->setLayout(outerLayout);

}

void DeadWindow::receive_dead(int deathN, int PlayerN, bool ifAuto)
{
    this->show();

    /*
     * edit death message here
     */

    if (deathN == 1 && PlayerN == 1 && !ifAuto)
    {
        start->setText(tr("You Died, Idiot!"));
        return;
    }
    if (deathN == 1 && PlayerN == 1 && ifAuto)
    {
        start->setText(tr("Delamain ain't Clever Enough..."));
        set_font_point_size(start, 33);
        return;
    }
    if (deathN == 1 && PlayerN == 2 && !ifAuto)
    {
        start->setText(tr("Player2 Wins!"));
        return;
    }
    if (deathN == 1 && PlayerN == 2 && ifAuto)
    {
        start->setText(tr("Delamain Just Beat You!"));
        set_font_point_size(start, 40);
        return;
    }
    if (deathN == 2 && !ifAuto)
    {
        start->setText(tr("Player1 Wins!"));
        return;
    }
    if (deathN == 2 && ifAuto)
    {
        start->setText(tr("You Beat Delamain!"));
        return;
    }
}

void DeadWindow::on_click_restart()
{
    this->hide();
    emit send_restart();
}

void DeadWindow::on_click_load()
{
    this->hide();
    emit send_load();
}

void DeadWindow::on_click_back()
{
    this->hide();
    emit send_back();
}
