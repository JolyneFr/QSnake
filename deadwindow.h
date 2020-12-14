#ifndef DEADWINDOW_H
#define DEADWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mybutton.h"
#include <QDialog>

class DeadWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DeadWindow(QWidget *parent = nullptr);

private:
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 600;

    void set_layout();

    QVBoxLayout *outerLayout;

signals:
    void send_restart();
    void send_load();
    void send_back();

private slots:
    void receive_dead();
    void on_click_restart();
    void on_click_load();
    void on_click_back();

};

#endif // DEADWINDOW_H
