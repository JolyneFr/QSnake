#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QApplication>
#include <QFontDatabase>
#include <QWidget>
#include <QString>
#include <QDebug>

/*
 * this file includes several functions that:
 * re-used by windows
 * too long to read & no need to adjust
 *
 */


/*
 * set font size of QWidget *obj
 * avoid code re-using
 */
void set_font_point_size(QWidget *obj, int size);

/*
 * set font of the game
 * add fonts to Resourses before use them
 */
void load_font(QString fontFileName);

enum BlockType{BackGround, Wall, Snake1, Snake2, Apple, LifeFruit, SpeedUp, SpeedDown, Exchange};

#endif // FUNCTIONS_H
