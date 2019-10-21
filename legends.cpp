#include "legends.h"

legends::legends(QWidget*parent):QWidget(parent)
{
    setupUi(this);
    updateColorLabel(parkLabel,QColor(201,225,169));
    updateColorLabel(squareLabel,QColor(210,210,210));
    updateColorLabel(residentialLabel,QColor(250,225,115));
    updateColorLabel(officeLabel,QColor(150,210,227));
    updateColorLabel(culturalLabel,QColor(255,170,170));
    updateColorLabel(commercialLabel,QColor(255,180,90));
    updateColorLabel(hotelLabel,QColor(198,183,213));
    updateColorLabel(civicColorLabel,QColor(155,179,202));

}
void legends::updateColorLabel(QLabel *label, const QColor &color)
{
    QPixmap pixmap(16,16);
    pixmap.fill(color);
    label->setPixmap(pixmap);
}
