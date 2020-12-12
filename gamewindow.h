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

private:
    static const int WINDOW_WIDTH = 600;
    static const int WINDOW_HEIGHT = 700;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 10;
    static const int APPLE_TIME_COUNTER = 50;
    int timeCounter;
    int height_pixel;
    int width_pixel;

    int PlayerN;

    bool isContinue;

    GameSence *thisGame;
    std::vector<GameSence*> *savedGames;
    int **canvas;
    QTimer *timer;
    int times;

    void init_canvas();
    void paint_canvas();
    void load_game(int gameIndex);



signals:
    void send_pause();

protected slots:
    void receive_continue_game();
    void receive_load_game();
    void save_current_game();
    void pause();
    void receive_enter_game(int playerNum);
    void timeout();

};

#endif // GAMEWINDOW_H
