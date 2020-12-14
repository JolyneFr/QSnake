#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QApplication>
#include <QFontDatabase>
#include <QWidget>
#include <QString>
#include <QDebug>

void set_font_point_size(QWidget *obj, int size);

void load_font(QString fontFileName);

#endif // FUNCTIONS_H