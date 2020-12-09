#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include <QApplication>
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
    static const int WINDOW_HEIGHT = 600;

    QVBoxLayout *outerLayout;

private slots:
    void show_select_window();
    void on_click_back();
    void on_click_singleplayer();
    void on_click_multiplayer();

signals:
    void back_to_menu();
    void enter_game(int playerNum);
};

#endif // SELECTWINDOW_H
