#include "qsnakewindow.h"

QsnakeWindow::QsnakeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Qsnake Made by JolyneFr"));
    setStyleSheet("background-color:gray;");
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

QsnakeWindow::~QsnakeWindow()
{
}

void paintEvent(QPaintEvent *)
{

}

void timerEvent(QTimerEvent *)
{

}

void keyPressEvent(QKeyEvent *)
{

}

