#include "qsnakestartwindow.h"

void setFontPointSize_start(QWidget *obj, int size)
{
    QFont ft;
    ft.setPointSize(size);
    obj->setFont(ft);
}

QsnakeStartWindow::QsnakeStartWindow(QWidget *parent)
    : QWidget(parent)
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


    /*     initialize the window     */

    setWindowTitle(tr("Qsnake Made by JolyneFr"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QVBoxLayout *outerLayout = new QVBoxLayout;

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 4));

    QHBoxLayout *topicLayout = new QHBoxLayout();
    QLabel * start = new QLabel("Q-SNAKE!");
    start->resize(500, 100);
    start->setAlignment(Qt::AlignCenter);
    setFontPointSize_start(start, 45);
    topicLayout->addWidget(start,5);
    outerLayout->addLayout(topicLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 3, 1));
    QVBoxLayout *buttons = new QVBoxLayout();

    myButton * startButton = new myButton(this);
    startButton->setText(tr("START"));
    buttons->addWidget(startButton);

    myButton * endButton = new myButton(this);
    endButton->setText(tr("QUIT"));
    connect(endButton, &QPushButton::clicked, this, &QsnakeStartWindow::close);
    buttons->addWidget(endButton);
    buttonLayout->addLayout(buttons);
    buttonLayout->addSpacerItem(new QSpacerItem(WINDOW_WIDTH / 3, 1));
    outerLayout->addLayout(buttonLayout);

    outerLayout->addSpacerItem(new QSpacerItem(1, WINDOW_HEIGHT / 5));
    connect(startButton, &QPushButton::clicked, this, &QsnakeStartWindow::on_click_start);
    this->setLayout(outerLayout);

}

QsnakeStartWindow::~QsnakeStartWindow()
{
}

//void paintEvent(QPaintEvent *)
//{

//}

//void timerEvent(QTimerEvent *)
//{

//}

//void keyPressEvent(QKeyEvent *)
//{

//}

void QsnakeStartWindow::on_click_start()
{
    this->hide();
    emit start_game();

}

void QsnakeStartWindow::show_start_window()
{
    this->show();
}
