#include "mybutton.h"

myButton::myButton(QWidget *parent) : QPushButton(parent)
{

    /*     edit my button style here     */

    resize(buttonWidth, buttonHeight);
    QFont ft;
    ft.setPointSize(fontSize);
    setFont(ft);

    /*-----change the button stylesheet here-----*/
    this->setStyleSheet("QPushButton{"
                        "background-color:rgba(100,240,100,100);"
                        "border-style:outset;"
                        "border-width:4px;"
                        "border-radius:10px;"
                        "border-color:rgba(255,255,255,200);"
                        "color:rgba(0,0,0,160);"
                        "padding:6px;"
                        "}"

                        "QPushButton:pressed{"
                        "background-color:rgba(100,255,100,200);"
                        "border-color:rgba(255,255,255,30);"
                        "border-style:inset;"
                        "color:rgba(0,0,0,100);"
                        "}"

                        "QPushButton:hover{"
                        "background-color:rgba(100,255,100,100);"
                        "border-color:rgba(255,255,255,200);"
                        "color:rgba(0,0,0,200);"
                        "}");
}

void myButton::enterEvent(QEvent *event)
{

}
