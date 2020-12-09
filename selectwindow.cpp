#include "selectwindow.h"

void setFontPointSize_select(QWidget *obj, int size)
{
    QFont ft;
    ft.setPointSize(size);
    obj->setFont(ft);
}

SelectWindow::SelectWindow(QWidget *parent) : QDialog(parent)
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

    setWindowTitle(tr("Select Your Game Mode"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QVBoxLayout *outerLayout = new QVBoxLayout();

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 8));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("Select Game Mode!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    setFontPointSize_select(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * singlePlayer = new myButton();
    singlePlayer->setText(tr("SinglePlayer"));
    connect(singlePlayer, &QPushButton::clicked, this, &SelectWindow::on_click_singleplayer);

    myButton * multiPlayer = new myButton();
    multiPlayer->setText(tr("MultiPlayer"));
    connect(multiPlayer, &QPushButton::clicked, this, &SelectWindow::on_click_multiplayer);

    buttons->addWidget(singlePlayer);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 20));
    buttons->addWidget(multiPlayer);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 6));

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
    emit back_to_menu();
}

void SelectWindow::on_click_singleplayer()
{
    this->hide();
    emit enter_game(1);
}

void SelectWindow::on_click_multiplayer()
{
    this->hide();
    emit enter_game(2);
}

void SelectWindow::show_select_window()
{
    this->show();
}


