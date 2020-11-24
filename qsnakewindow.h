#ifndef QSNAKEWINDOW_H
#define QSNAKEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

class QsnakeWindow : public QMainWindow
{
    Q_OBJECT

public:
    QsnakeWindow(QWidget *parent = nullptr);
    ~QsnakeWindow();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    static const int WINDOW_WIDTH = 700;
    static const int WINDOW_HEIGHT = 600;
};
#endif // QSNAKEWINDOW_H
