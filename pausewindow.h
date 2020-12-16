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
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    void set_layout();

    QVBoxLayout *outerLayout;

    int **canvas;

signals:
    void send_continue(int **);
    void send_save();
    void send_load();
    void send_back();
    void send_edit(int, int**);

private slots:
    void receive_pause(int **);
    void on_click_continue();
    void on_click_save();
    void on_click_load();
    void on_click_back();
    void on_click_edit();


};

#endif // PAUSEWINDOW_H
