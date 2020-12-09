#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QColor>
#include <QTimer>
#include <QTime>
#include <QApplication>
#include <QPainter>
#include "gamesence.h"
#include "mybutton.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timeout();

private:
    static const int WINDOW_WIDTH = 600;
    static const int WINDOW_HEIGHT = 700;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 10;
    int height_pixel;
    int width_pixel;

    int PlayerN;

    bool isContinue;

    GameSence *thisGame;
    std::vector<GameSence*> savedGames;
    int **canvas;
    QTimer *timer;

    void init_canvas();
    void paint_canvas();



signals:

private slots:
    void receive_enter_game(int playerNum);

};

#endif // GAMEWINDOW_H
