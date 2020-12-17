#include "qsnakestartwindow.h"
#include "functions.h"

QsnakeStartWindow::QsnakeStartWindow(QWidget *parent)
    : QWidget(parent)
{

    /*     initialize the window     */

    setWindowTitle(tr("Qsnake Made by JolyneFr"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    set_layout();

}

void QsnakeStartWindow::set_layout()
{

    setStyleSheet("background-color: seashell");

    QVBoxLayout *outerLayout = new QVBoxLayout;

    //outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("Q-SNAKE!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    set_font_point_size(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    //outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 4, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * continueButton = new myButton(this);
    continueButton->setText(tr("CONTINUE"));
    buttons->addWidget(continueButton);
    connect(continueButton, &QPushButton::clicked, this, &QsnakeStartWindow::on_click_continue);

    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));

    myButton * startButton = new myButton(this);
    startButton->setText(tr("NEW GAME"));
    buttons->addWidget(startButton);

    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));

    myButton * editButton = new myButton(this);
    editButton->setText(tr("EDIT CANVAS"));
    buttons->addWidget(editButton);
    connect(editButton, &QPushButton::clicked, this, &QsnakeStartWindow::on_click_edit);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));


    myButton * endButton = new myButton(this);
    endButton->setText(tr("QUIT"));
    connect(endButton, &QPushButton::clicked, this, &QsnakeStartWindow::close);
    buttons->addWidget(endButton);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 4, 1));
    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));
    connect(startButton, &QPushButton::clicked, this, &QsnakeStartWindow::on_click_start);
    this->setLayout(outerLayout);

}

void QsnakeStartWindow::on_click_start()
{
    this->hide();
    emit send_start(nullptr);
}

void QsnakeStartWindow::on_click_continue()
{
    this->hide();
    emit send_load_continue();
}

void QsnakeStartWindow::on_click_edit()
{
    this->hide();
    emit send_edit(1, nullptr);
}

void QsnakeStartWindow::receive_back()
{
    this->show();
}
