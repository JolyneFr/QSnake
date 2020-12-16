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
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    void set_layout();

    QVBoxLayout *outerLayout;


private slots:
    void receive_back();
    void on_click_start();
    void on_click_continue();

signals:
    void send_start();
    void send_load_continue();
};
#endif // QsnakeStartWindow_H
