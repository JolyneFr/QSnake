#include "pausewindow.h"
#include "functions.h"

PauseWindow::PauseWindow(QWidget *parent) : QDialog(parent)
{


    setWindowTitle(tr("You Can't Escape."));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    set_layout();
}

void PauseWindow::set_layout()
{

    QVBoxLayout *outerLayout = new QVBoxLayout();

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 20));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("PAUSE!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    set_font_point_size(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 20));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * continueButton = new myButton();
    continueButton->setText(tr("Continue"));
    connect(continueButton, &QPushButton::clicked, this, &PauseWindow::on_click_continue);


    myButton * saveButton = new myButton();
    saveButton->setText(tr("Save Game"));
    connect(saveButton, &QPushButton::clicked, this, &PauseWindow::on_click_save);

    myButton * loadButton = new myButton();
    loadButton->setText(tr("Load Game"));
    connect(loadButton, &QPushButton::clicked, this, &PauseWindow::on_click_load);

    myButton * editButton = new myButton();
    editButton->setText(tr("Edit Canvas"));
    connect(editButton, &QPushButton::clicked, this, &PauseWindow::on_click_edit);


    myButton * backButton = new myButton();
    backButton->setText(tr("Back to MainWindow"));
    connect(backButton, &QPushButton::clicked, this, &PauseWindow::on_click_back);

    buttons->addWidget(continueButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(saveButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(loadButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(editButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 70));
    buttons->addWidget(backButton);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

    this->setLayout(outerLayout);
}

void PauseWindow::receive_pause(int **receiveCanvas)
{
    canvas = receiveCanvas;
    this->show();
}

void PauseWindow::on_click_continue()
{
    this->hide();
    emit send_continue();
}

void PauseWindow::on_click_save()
{
    emit send_save();
}

void PauseWindow::on_click_back()
{
    this->hide();
    emit send_back();
}

void PauseWindow::on_click_load()
{
    this->hide();
    emit send_load();
}
void PauseWindow::on_click_edit()
{
    this->hide();
    emit send_edit(2, canvas);
}
