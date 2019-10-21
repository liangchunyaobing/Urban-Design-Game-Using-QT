#include"block.h"
#include"BlockPropertiesDialog.h"

BlockPropertiesDialog::BlockPropertiesDialog(block*bl,QWidget*parent)
    :QDialog(parent)
{
    setupUi(this);
    this->bl=bl;
    xSpinBox->setValue(int(bl->x()));
    ySpinBox->setValue(int(bl->y()));
    WidthSpinBox->setValue(bl->boundingRect().width());
    HeightSpinBox->setValue(bl->boundingRect().height());
}

void BlockPropertiesDialog::on_buttonBox_accepted(){
    bl->setPos(xSpinBox->value(),ySpinBox->value());
    bl->setWidth(WidthSpinBox->value());
    bl->setHeight(HeightSpinBox->value());
    QDialog::accept();
}
