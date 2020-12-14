#include "functions.h"

void set_font_point_size(QWidget *obj, int size)
{
    QFont ft;
    ft.setPointSize(size);
    obj->setFont(ft);
}

void load_font(QString fontFileName)
{
    int fontId = QFontDatabase::addApplicationFont(fontFileName);
    QStringList fontIDs = QFontDatabase::applicationFontFamilies(fontId);
    if (! fontIDs.isEmpty()) {
        QFont font(fontIDs.first());
        QApplication::setFont(font);
    }
    else {
        qDebug() << "Failed to load font.";
    }
}
