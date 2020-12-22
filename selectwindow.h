#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mybutton.h"
#include <QDialog>

class SelectWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SelectWindow(QWidget *parent = nullptr);

private:
    /*
     *    preset data to init the window
     *    free to change
     */
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    /*
     * store the size of canvas
     * for carrying the game canvas
     */
    static const int width_pixel = 20;
    static const int height_pixel = 20;

    /*
     * window layout
     */
    void set_layout();
    QVBoxLayout *outerLayout;

    /*
     * store & clone the edited canvas to game window
     * clone is necessary to avoid snake hazard
     */
    int **get_canvas_clone();
    int **carriedCanvas;

private slots:
    void receive_start(int **canvas);
    void on_click_back();
    void on_click_singleplayer();
    void on_click_multiplayer();
    void on_click_aifight();
    void on_click_aishow();

signals:
    void send_back();
    void send_enter(int playerNum, int **canvas);
};

#endif // SELECTWINDOW_H
