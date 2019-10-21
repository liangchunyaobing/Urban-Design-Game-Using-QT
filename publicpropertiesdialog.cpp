#include"publicspace.h"
#include"publicpropertiesdialog.h"

PublicPropertiesDialog::PublicPropertiesDialog(publicspace*p,QWidget*parent)
    :QDialog(parent)
{
    setupUi(this);
    this->p=p;
    xSpinBox->setValue(int(p->x()));
    ySpinBox->setValue(int(p->y()));
    WidthSpinBox->setValue(p->boundingRect().width());
    HeightSpinBox->setValue(p->boundingRect().height());
    FunctionComboBox->setCurrentIndex(p->getFunction());
}

void PublicPropertiesDialog::on_buttonBox_accepted(){
    p->setPos(xSpinBox->value(),ySpinBox->value());
    p->setRect(-WidthSpinBox->value()/2,-HeightSpinBox->value()/2,
               WidthSpinBox->value(),HeightSpinBox->value());
    p->setFunction(publicspace::Function(FunctionComboBox->currentIndex()));
    QDialog::accept();   
}
