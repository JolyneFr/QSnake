#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mybutton.h"
#include <QDialog>

class PauseWindow : public QDialog
{
    Q_OBJECT
public:
    explicit PauseWindow(QWidget *parent = nullptr);

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
    QVBoxLayout *outerLayout;

    /*
     * current game canvas for possible edit action
     */
    int **canvas;

signals:
    void send_continue();
    void send_save();
    void send_load();
    void send_back();
    void send_edit(int caller, int** canvas); // caller = 2 by default

private slots:
    void receive_pause(int **canvas);
    void on_click_continue();
    void on_click_save();
    void on_click_load();
    void on_click_back();
    void on_click_edit();


};

#endif // PAUSEWINDOW_H
