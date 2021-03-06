#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QButtonGroup>
#include "mybutton.h"
#include "functions.h"

class EditWindow : public QDialog
{
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    /*
     * const window & canvas arguements
     * DO NOT CHANGE
     * or change all windows arguement including these figures
     *
     * WINDOW_WIDTH / HEIGHT: pixel size of window
     * CANVAS_WIDTH / HEIGHT: pixel size of game canvas
     * pixel: side cheif of one game brick
     *
     */
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 750;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 20;

    /*
     * window layout
     */
    QHBoxLayout * outerLayout;
    QButtonGroup * colorButtons;

    /*
     * edited canvas
     * initialized when window constructed
     * if called by pause window, set to new canvas
     *
     */
    int **canvas;

    /*
     * caller of edit window
     * initialized when called
     * 1: main window
     * 2: pause window
     *
     */
    int caller;

    void set_layout();
    void init_canvas();

    /*
     * get selected color-type of painter
     * return -1 if no color is selected
     *
     */
    int painterColorType();

signals:
    void send_back_to_menu();   // go back to main window
    void send_back_to_pause();  // go back to pause window
    void send_start(int **);    // start new game with edited canvas (arg: edited canvas)
    void send_continue();       // continue game with edited canvas

private slots:
    /*
     * receive_edit: called by main window / pause window
     * int **canvas = nullptr if called from main window
     *
     */
    void receive_edit(int caller, int** canvas);

    /*
     * slots functions when click certain button
     */
    void on_click_back();
    void on_click_run();

};

#endif // EDITWINDOW_H
