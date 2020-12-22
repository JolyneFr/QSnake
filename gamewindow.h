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

    /*
     * const window & canvas arguements
     * DO NOT CHANGE
     * or change all windows arguement including these figures
     *
     * WINDOW_WIDTH / HEIGHT: pixel size of window
     * CANVAS_WIDTH / HEIGHT: pixel size of game canvas
     * pixel: side cheif of one game brick
     * times: fixed refresh time (ms)
     *
     */
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 750;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 30;
    static const int times = 30;

    /*
     * window layout
     */
    QHBoxLayout *outerLayout;
    QLabel *scoreLabel1;
    QLabel *scoreLabel2;
    QLabel *lifeLabel1;
    QLabel *lifeLabel2;
    QLabel *speedLabel1;
    QLabel *speedLabel2;

    /*
     * color-string of bricks
     * edit color here if you have better choice
     * color name reference: https://www.w3.org/TR/SVG11/types.html#ColorKeywords
     */
    QString colorType[9] = {"white", "grey", "orange", "navy", "red", "green", "blue", "purple", "deeppink"};

    /*
     * count the time after game started
     * to impl different snake speed (using mod)
     */
    int timeCounter;

    /*
     * abstruct size of game canvas
     * equals to CANVAS_WIDTH / pixel & CANVAS_HEIGHT / pixel
     */
    int height_pixel;
    int width_pixel;

    /*
     * number of snake(s) on canvas
     * init when constructed
     * changed when load game
     */
    int PlayerN;

    /*
     * whether continue running
     * if == false, pause / dead window will be called
     */
    bool isContinue;

    GameSence *thisGame;

    /*
     * played canvas
     * showed by paint_canvas()
     */
    int **canvas;

    /*
     * initialized canvas by edit window
     * no snake here, save for restart function
     */
    int **defaultCanvas;

    /*
     * time counter for timeout event
     */
    QTimer *timer;

    /*
     * functions that you can guess feature by their names
     * encapsulated for briefing the codes
     */
    void init_canvas();
    void paint_canvas();
    void set_layout();
    void update_labels();
    void update_apples();
    void check_death();
    void exchange_snakes();
    void restart();
    int **get_canvas_clone(int **originCanvas);
    void move_snake(int snakeIndex);
    void load_game(QString filePath);



signals:

    /*
     * when press Key::Space, call pause window
     * send current gameCanvas for possible editing action
     */
    void send_pause(int **canvas);

    /*
     * go back to main window (won't save implicitly).
     */
    void send_back_to_menu();

    /*
     * send signal to dead window when game is over
     *
     * i: index of dead (defeated) snake
     * n: number of snake(s) on the canvas
     * f: whether the game includes AI snake
     *
     */
    void send_dead(int i, int n, bool f);

protected slots:

    /*
     * slots connected with pause window
     */
    void receive_continue_game();
    void receive_load_game();
    void receive_restart();
    void receive_save();

    /*
     * slots connected with other windows
     * called receive_enter_game every time when select "NEW GAME"
     */
    void receive_enter_game(int playerNum, int **canvas);
    void receive_load_continue();

    void on_press_pause();

    /*
     * key function: update all window every time timeout() is called
     */
    void timeout();

};

#endif // GAMEWINDOW_H
