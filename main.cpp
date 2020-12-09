#include "qsnakestartwindow.h"
#include "selectwindow.h"
#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QsnakeStartWindow w;
    SelectWindow s;
    GameWindow g;
    w.show();

    QObject::connect(&w, SIGNAL(start_game()), &s, SLOT(show_select_window()));
    QObject::connect(&s, SIGNAL(back_to_menu()), &w, SLOT(show_start_window()));
    QObject::connect(&s, SIGNAL(enter_game(int)), &g, SLOT(receive_enter_game(int)));

    return a.exec();
}
