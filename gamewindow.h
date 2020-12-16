#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QColor>
#include <QTimer>
#include <QPainter>
#include <string.h>
#include <QString>
#include <QDialog>
#include "gamesence.h"
#include "mybutton.h"

class GameWindow : public QDialog
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 750;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 30;
    static const int times = 30;
    static const int APPLE_TIME_COUNTER = 50;

    QHBoxLayout *outerLayout;
    QLabel *scoreLabel1;
    QLabel *scoreLabel2;
    QLabel *lifeLabel1;
    QLabel *lifeLabel2;
    QLabel *speedLabel1;
    QLabel *speedLabel2;

    QString colorType[9] = {"white", "grey", "orange", "navy", "red", "green", "blue", "purple", "pink"};

    int timeCounter;
    int height_pixel;
    int width_pixel;

    int PlayerN;

    bool isContinue;

    GameSence *thisGame;

    std::vector<GameSence*> *savedGames;

    int **canvas;
    QTimer *timer;

    void init_canvas();
    void paint_canvas();
    void set_layout();
    void update_labels();
    void update_apples();
    void check_death();
    void exchange_snakes();
    void move_snake(int);
    void load_game(int gameIndex);
    void restart();



signals:
    void send_pause();
    void send_back_to_menu();
    void send_dead(int i, int n, bool f);

protected slots:
    void receive_continue_game();
    void receive_load_game();
    void receive_restart();
    void receive_save();
    void receive_enter_game(int playerNum, int **canvas);
    void receive_load_continue();

    void on_press_pause();
    void timeout();

};

#endif // GAMEWINDOW_H
