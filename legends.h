#ifndef LEGENDS_H
#define LEGENDS_H

#include <ui_legends.h>
#include <QWidget>

class legends:public QWidget,private Ui::Legends
{
public:
    legends(QWidget*parent=nullptr);

private:
    void updateColorLabel(QLabel *label, const QColor &color);
};


#endif // LEGENDS_H
