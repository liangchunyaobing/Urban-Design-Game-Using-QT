#include "indexdialog.h"
#include "publicspace.h"

IndexDialog::IndexDialog(QWidget*parent):QDialog (parent)
{
    setupUi(this);
    siteAreaLabel->setText("1440000");
    GreenRatioLabel->setText("0");
    FloorRatioLabel->setText("0");

    publicLabel->setText(QString::number(publicspace::getnTotalArea()));
    parkLabel->setText(QString::number(publicspace::getnTotalParkArea()));
    SquareLabel->setText(QString::number(publicspace::getnTotalArea()-
                                         publicspace::getnTotalParkArea()));
    BuildingLabel->setText("0");
    ResidentialLabel->setText("0");
    OfficeLabel->setText("0");
 }
