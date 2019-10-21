#include "index.h"
#include "publicspace.h"
#include "building.h"

index::index(QWidget*parent):QWidget(parent){
    setupUi(this);

    siteArea=1440000;
    GreenRatio=parkArea/siteArea;
    publicArea=publicspace::getnTotalArea();
    parkArea=publicspace::getnTotalParkArea();
    buildingArea=building::getnArea();
    buildingTotalArea=building::getnTotalArea();
    buildingCoverage=buildingArea/siteArea;
    floorRatio=buildingTotalArea/siteArea;

    siteAreaLabel->setText("1440000");
    PublicAreaLabel->setText(QString::number(publicArea));
    GreenAreaLabel->setText(QString::number(parkArea));
    GreenRatioLabel->setText(QString::number(GreenRatio));
    buildingAreaLabel->setText(QString::number(buildingArea));
    buildTotolAreaLabel->setText(QString::number(buildingTotalArea));
    BuildingCoverageLabel->setText(QString::number(buildingCoverage));
    FloorRatioLabel->setText(QString::number(floorRatio));
    connect(updateButton,SIGNAL(clicked()),this,SLOT(updateIndex()));
};

void index::updateIndex(){
    GreenRatio=parkArea/siteArea;
    publicArea=publicspace::getnTotalArea();
    parkArea=publicspace::getnTotalParkArea();
    buildingArea=building::getnArea();
    buildingTotalArea=building::getnTotalArea();
    buildingCoverage=buildingArea/siteArea;
    floorRatio=buildingTotalArea/siteArea;

    PublicAreaLabel->setText(QString::number(publicArea));
    GreenAreaLabel->setText(QString::number(parkArea));
    GreenRatioLabel->setText(QString::number(GreenRatio));
    buildingAreaLabel->setText(QString::number(buildingArea));
    buildTotolAreaLabel->setText(QString::number(buildingTotalArea));
    BuildingCoverageLabel->setText(QString::number(buildingCoverage));
    FloorRatioLabel->setText(QString::number(floorRatio));
    QWidget::update();
}

//index::index(index &i){
//    setupUi(this);
//    siteAreaLabel->setText(i.siteAreaLabel->text());
//    GreenRatioLabel->setText(i.GreenRatioLabel->text());
//    FloorRatioLabel->setText(i.siteAreaLabel->text());

//    publicLabel->setText(i.publicLabel->text());
//    parkLabel->setText(i.parkLabel->text());
//    SquareLabel->setText(i.SquareLabel->text());

//    BuildingLabel->setText(i.BuildingLabel->text());
//    ResidentialLabel->setText(i.ResidentialLabel->text());
//    OfficeLabel->setText(i.OfficeLabel->text());
//}
