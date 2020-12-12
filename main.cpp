#include "qsnakestartwindow.h"
#include "selectwindow.h"
#include "gamewindow.h"
#include "pausewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QsnakeStartWindow w;
    SelectWindow s;
    GameWindow g;
    PauseWindow p;
    w.show();

    QObject::connect(&w, SIGNAL(start_game()), &s, SLOT(show_select_window()));
    QObject::connect(&s, SIGNAL(back_to_menu()), &w, SLOT(show_start_window()));
    QObject::connect(&s, SIGNAL(enter_game(int)), &g, SLOT(receive_enter_game(int)));
    QObject::connect(&g, SIGNAL(send_pause()), &p, SLOT(receive_pause()));
    QObject::connect(&p, SIGNAL(continue_game()), &g, SLOT(receive_continue_game()));
    QObject::connect(&p, SIGNAL(save_game()), &g, SLOT(save_current_game()));
    QObject::connect(&p, SIGNAL(load_game()), &g, SLOT(receive_load_game()));

    return a.exec();
}
