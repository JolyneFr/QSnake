#ifndef QSNAKE_STARTWINDOW_H
#define QSNAKE_STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mybutton.h"

class QsnakeStartWindow : public QWidget
{
    Q_OBJECT

public:
    QsnakeStartWindow(QWidget *parent = nullptr);

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


private slots:
    void receive_back();
    void on_click_start();
    void on_click_continue();
    void on_click_edit();

signals:

    /*
     * when calling start by main window, game canvas is set to nullptr
     * re-impl in edit window
     */
    void send_start(int **canvas);
    void send_load_continue();
    void send_edit(int caller, int** canvas); // caller = 1 by default
};
#endif // QsnakeStartWindow_H
