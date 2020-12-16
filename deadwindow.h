#ifndef DEADWINDOW_H
#define DEADWINDOW_H

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include "mybutton.h"

class DeadWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DeadWindow(QWidget *parent = nullptr);

private:

    /*     preset data to init the window     */
    /*     free to change                     */
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 700;

    /*     window layout     */
    void set_layout();
    QLabel * start;
    QVBoxLayout *outerLayout;

signals:
    void send_restart();
    void send_load();
    void send_back();

private slots:
    void receive_dead(int i, int n, bool f);
    void on_click_restart();
    void on_click_load();
    void on_click_back();

};

#endif // DEADWINDOW_H
