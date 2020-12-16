#include "qsnakestartwindow.h"
#include "selectwindow.h"
#include "gamewindow.h"
#include "pausewindow.h"
#include "deadwindow.h"
#include "editwindow.h"
#include "functions.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_font(":/Font/AlegreyaSans-BoldItalic.ttf");
    QsnakeStartWindow w;
    SelectWindow s;
    GameWindow g;
    PauseWindow p;
    DeadWindow d;
    EditWindow e;
    w.show();

    /*-----Connect All Signals & Slots Between Windows-----*/

    QObject::connect(&w, SIGNAL(send_start(int **)), &s, SLOT(receive_start(int **)));
    QObject::connect(&s, SIGNAL(send_back()), &w, SLOT(receive_back()));
    QObject::connect(&s, SIGNAL(send_enter(int, int**)), &g, SLOT(receive_enter_game(int, int**)));
    QObject::connect(&g, SIGNAL(send_pause()), &p, SLOT(receive_pause()));
    QObject::connect(&p, SIGNAL(send_continue()), &g, SLOT(receive_continue_game()));
    QObject::connect(&p, SIGNAL(send_save()), &g, SLOT(receive_save()));
    QObject::connect(&p, SIGNAL(send_load()), &g, SLOT(receive_load_game()));
    QObject::connect(&g, SIGNAL(send_dead(int, int, bool)), &d, SLOT(receive_dead(int, int, bool)));
    QObject::connect(&d, SIGNAL(send_restart()), &g, SLOT(receive_restart()));
    QObject::connect(&d, SIGNAL(send_load()), &g, SLOT(receive_load_game()));
    QObject::connect(&d, SIGNAL(send_back()), &w, SLOT(receive_back()));
    QObject::connect(&w, SIGNAL(send_load_continue()), &g, SLOT(receive_load_continue()));
    QObject::connect(&p, SIGNAL(send_back()), &w, SLOT(receive_back()));
    QObject::connect(&w, SIGNAL(send_edit(int)), &e, SLOT(receive_edit(int)));
    QObject::connect(&e, SIGNAL(send_back_to_menu()), &w, SLOT(receive_back()));
    QObject::connect(&e, SIGNAL(send_start(int **)), &s, SLOT(receive_start(int **)));
    QObject::connect(&g, SIGNAL(send_back_to_menu()), &w, SLOT(receive_back()));

    return a.exec();
}
