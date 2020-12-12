#include "pausewindow.h"

void FontPointSize_select(QWidget *obj, int size)
{
    QFont ft;
    ft.setPointSize(size);
    obj->setFont(ft);
}

PauseWindow::PauseWindow(QWidget *parent) : QDialog(parent)
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

    setWindowTitle(tr("You Can't Escape."));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QVBoxLayout *outerLayout = new QVBoxLayout();

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 8));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("PAUSE!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    FontPointSize_select(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 10));

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
    loadButton->setText("Load Game");
    connect(loadButton, &QPushButton::clicked, this, &PauseWindow::on_click_load);

    buttons->addWidget(continueButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 25));
    buttons->addWidget(saveButton);
    buttons->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 25));
    buttons->addWidget(loadButton);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 5, 1));

    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 6));

    this->setLayout(outerLayout);
}

void PauseWindow::receive_pause()
{
    this->show();
}

void PauseWindow::on_click_continue()
{
    this->hide();
    emit continue_game();
}

void PauseWindow::on_click_save()
{
    emit save_game();
}

void PauseWindow::on_click_load()
{
    this->hide();
    emit load_game();
}
