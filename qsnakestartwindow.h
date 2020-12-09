#ifndef QSNAKE_STARTWINDOW_H
#define QSNAKE_STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFontDatabase>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mybutton.h"

class QsnakeStartWindow : public QWidget
{
    Q_OBJECT

public:
    QsnakeStartWindow(QWidget *parent = nullptr);
    ~QsnakeStartWindow();


//protected:
//    void paintEvent(QPaintEvent *);
//    void timerEvent(QTimerEvent *);
//    void keyPressEvent(QKeyEvent *);

private:
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 600;

    QVBoxLayout *outerLayout;


private slots:
    void show_start_window();
    void on_click_start();

signals:
    void start_game();
};
#endif // QsnakeStartWindow_H
