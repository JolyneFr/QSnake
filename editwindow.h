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
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 750;
    static const int CANVAS_WIDTH = 600;
    static const int CANVAS_HEIGHT = 600;
    static const int pixel = 30;

    QHBoxLayout * outerLayout;
    QButtonGroup * colorButtons;
    int **canvas;
    int caller;   // 1: menu  2: pause

    void set_layout();
    void init_canvas();

    int painterColorType();

signals:
    void send_back_to_menu();
    void send_back_to_pause();
    void send_start(int **);

private slots:
    void receive_edit(int);
    void on_click_back();
    void on_click_run();

};

#endif // EDITWINDOW_H
