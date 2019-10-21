#include<QtGui>

#include"building.h"
#include"BuildingPropertiesDialog.h"

BuildingPropertiesDialog::BuildingPropertiesDialog(building*b,QWidget*parent)
    :QDialog(parent)
{
    setupUi(this);
    this->b=b;
    xSpinBox->setValue(int(b->x()));
    ySpinBox->setValue(int(b->y()));
    WidthSpinBox->setValue(b->boundingRect().width());
    HeightSpinBox->setValue(b->boundingRect().height());
    LayerSpinBox->setValue(b->getLayer());
    FunctionComboBox->setCurrentIndex(b->getFunction());
 }

void BuildingPropertiesDialog::on_buttonBox_accepted(){
    b->setPos(xSpinBox->value(),ySpinBox->value());
    b->setRect(-WidthSpinBox->value()/2,-HeightSpinBox->value()/2,
               WidthSpinBox->value(),HeightSpinBox->value());
    b->setLayer(LayerSpinBox->value());
    b->setFunction(building::Function(FunctionComboBox->currentIndex()));
    QDialog::accept();
}


