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
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    void set_layout();

    QVBoxLayout *outerLayout;
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
