#include "editwindow.h"
#include <QDebug>

QString colorType[9] = {"white", "grey", "orange", "navy", "red", "green", "blue", "purple", "pink"};
QString blockName[9] = {"BackGround", "Wall", "Snake1", "Snake2", "Apple", "LifeFruit", "SpeedUp", "SpeedDown", "Exchange"};

EditWindow::EditWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Edit Game Canvas Here!"));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    set_layout();

    init_canvas();

}

void EditWindow::set_layout()
{
    outerLayout = new QHBoxLayout();



    QVBoxLayout *leftLayout = new QVBoxLayout();

    QHBoxLayout *topLayout = new QHBoxLayout();




    leftLayout->addLayout(topLayout);

    myButton * save = new myButton();
    save->setText(tr("Save && Run!"));
    topLayout->addWidget(save);
    connect(save, &QPushButton::clicked, this, &EditWindow::on_click_run);

    myButton * back = new myButton();
    back->setText(tr("Back"));
    topLayout->addWidget(back);
    connect(back, &QPushButton::clicked, this, &EditWindow::on_click_back);
    leftLayout->addSpacerItem(new QSpacerItem(CANVAS_WIDTH, CANVAS_HEIGHT));

    outerLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();

    colorButtons = new QButtonGroup();
    colorButtons->setExclusive(true);

    QLabel *words = new QLabel(tr("Select A Brick"));
    words->resize(WINDOW_WIDTH - CANVAS_WIDTH, WINDOW_HEIGHT - CANVAS_HEIGHT);
    set_font_point_size(words, 20);

    rightLayout->addWidget(words);

    for (int i = 0; i < 9; i++)
    {
        if (i == 2 || i == 3) continue;

        myButton * color = new myButton();
        color->setCheckable(true);
        color->setText(blockName[i]);
        set_font_point_size(color, 20);
        //color->setText("color:" + colorType[i]);
        rightLayout->addWidget(color);
        rightLayout->addSpacerItem(new QSpacerItem(1, 12));
        colorButtons->addButton(color);
        colorButtons->setId(color, i);
    }

    outerLayout->addLayout(rightLayout);

    this->setLayout(outerLayout);
}

void EditWindow::init_canvas()
{
    int width_pixel = CANVAS_WIDTH / pixel;
    int height_pixel = CANVAS_HEIGHT / pixel;

    canvas = new int*[width_pixel];

    for(int i = 0; i < width_pixel; i++)
    {
        canvas[i] = new int[height_pixel];
        memset(canvas[i], 0, height_pixel *sizeof(int));
    }

    for (int i = 0; i < height_pixel; i++)
    {
        canvas[0][i] = BlockType::Wall;
        canvas[width_pixel - 1][i] = BlockType::Wall;
    }

    for (int i = 1; i < width_pixel - 1; i++)
    {
        canvas[i][0] = BlockType::Wall;
        canvas[i][height_pixel - 1] = BlockType::Wall;
    }
}

void EditWindow::paintEvent(QPaintEvent *event)
{
    int width_pixel = CANVAS_WIDTH / pixel;
    int height_pixel = CANVAS_HEIGHT / pixel;

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

void EditWindow::mousePressEvent(QMouseEvent *event)
{
    int realX = event->x();
    int realY = event->y();

    int x = realX / pixel;
    int y = (realY - (WINDOW_HEIGHT - CANVAS_HEIGHT)) / pixel;

    if (x <= 0 || x >= CANVAS_WIDTH / pixel - 1 || y <= 0 || y >= CANVAS_HEIGHT / pixel - 1)
    {
        qDebug() << "mouse out of bound.";
        return;
    }

    if (painterColorType() == -1)
    {
        qDebug() << "select a bricktype first!";
        return;
    }

    if (canvas[x][y] == BlockType::Snake1 || canvas[x][y] == BlockType::Snake2)
    {
        qDebug() << "invalid position.";
        return;
    }

    qDebug() << "success: " << painterColorType();

    canvas[x][y] = painterColorType();

    update();
}

int EditWindow::painterColorType()
{
    return colorButtons->checkedId();
}

void EditWindow::receive_edit(int _caller, int **curCanvas)
{
    caller = _caller;
    if (caller == 1)
    {
        init_canvas();
    }
    else
    {
        canvas = curCanvas;
    }

    this->show();
}

void EditWindow::on_click_run()
{
    this->hide();
    if (caller == 1)
    {
        emit send_start(canvas);
    }
    else
    {
        emit send_continue(canvas);
    }
}

void EditWindow::on_click_back()
{
    this->hide();
    if (caller == 1)
    {
        emit send_back_to_menu();
    }
    else
    {
        emit send_back_to_pause();
    }
}
