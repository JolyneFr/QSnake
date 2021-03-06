#ifndef MYBOTTON_H
#define MYBOTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

/*
 * impl my own button class
 * define styleSheet to edit
 */

class myButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myButton(QWidget *parent = nullptr);

    void enterEvent(QEvent *event);

private:

    static const int buttonHeight = 60;
    static const int buttonWidth = 250;
    static const int fontSize = 25;

signals:

};

#endif // MYBOTTON_H
