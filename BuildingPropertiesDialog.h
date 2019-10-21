#ifndef PROPERTIESDIALOGUE_H
#define PROPERTIESDIALOGUE_H

#include"ui_BuildingPropertiesDialog.h"
#include "building.h"

//class building;

class BuildingPropertiesDialog:public QDialog,private Ui::BuildingPropertiesDialog{
    Q_OBJECT
public:
    BuildingPropertiesDialog(building*b,QWidget*parent=nullptr);

private slots:
    void on_buttonBox_accepted();

private:
    building*b;
};

#endif // PROPERTIESDIALOGUE_H
