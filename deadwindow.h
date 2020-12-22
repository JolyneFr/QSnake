#ifndef DEADWINDOW_H
#define DEADWINDOW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include "mybutton.h"

class DeadWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DeadWindow(QWidget *parent = nullptr);

private:

    /*
     *    preset data to init the window
     *    free to change
     */
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    /*
     * window layout
     */
    void set_layout();
    QLabel * start;
    QVBoxLayout *outerLayout;

signals:
    void send_restart(); // restart game with the default canvas
    void send_load();    // load game from file (send ERROR if file doesn't exist).
    void send_back();    // go back to main window (won't save implicitly).

private slots:
    /*
     * receive_dead: called from game window when game is over
     *
     * i: index of dead (defeated) snake
     * n: number of snake(s) on the canvas
     * f: whether the game includes AI snake
     *
     */
    void receive_dead(int i, int n, bool f);

    /*
     * slots functions when click certain button
     */
    void on_click_restart();
    void on_click_load();
    void on_click_back();

};

#endif // DEADWINDOW_H
