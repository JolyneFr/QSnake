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

signals:
    void send_continue();
    void send_save();
    void send_load();
    void send_back();

private slots:
    void receive_pause();
    void on_click_continue();
    void on_click_save();
    void on_click_load();
    void on_click_back();


};

#endif // PAUSEWINDOW_H
