#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include <QApplication>
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
    static const int WINDOW_HEIGHT = 600;

    QVBoxLayout *outerLayout;

signals:
    void continue_game();
    void save_game();
    void load_game();

private slots:
    void receive_pause();
    void on_click_continue();
    void on_click_save();
    void on_click_load();


};

#endif // PAUSEWINDOW_H
