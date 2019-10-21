#include <QtGui>
#include <cmath>
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>

#include "cityscape.h"
#include "building.h"
#include "cityview.h"
#include "publicspace.h"
#include "block.h"
#include "BuildingPropertiesDialog.h"
#include "BlockPropertiesDialog.h"
#include "publicpropertiesdialog.h"
#include "index.h"
#include "user.h"

class index;
class user;
class QDockWidget;

cityscape::cityscape()
{
    scene=new QGraphicsScene(-50,-50,1600,900);
    scene->setBackgroundBrush(QColor(255,255,255));
    //scene->setBackgroundBrush(QColor(255,246,202));
    generateCityBlocks();

    view=new CityView;
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    //view->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);

    createActions();
    createMenus();
    createToolBars();
    createDockWindows();
    connect(scene,SIGNAL(selectionChanged()),this,SLOT(updateActions()));
    setWindowTitle(tr("Cityscape"));
    updateActions();
}

void cityscape::generateCityBlocks(){
    for(int x=0;x<16;++x){
        for(int y=0;y<9;++y){
            block *bl=new block(93,93);
            bl->setPos(QPoint(x*100+40,y*100+40));
            scene->addItem(bl);
            int percentile=std::rand()%7;
            if(percentile==0){
                publicspace::Function func;
                func=publicspace::Function(std::rand()%2);
                publicspace *p=new publicspace(func);
                p->setRect(-40,-40,80,80);
                p->setPos(QPoint(x*100+40,y*100+40));
                scene->addItem(p);
            }else if(percentile==1||percentile==2||percentile==3){
                building::Function func_1;
                func_1=building::Function(std::rand()%6);
                building::Function func_2;
                func_2=building::Function(std::rand()%6);
                building::Function func_3;
                func_3=building::Function(std::rand()%6);
                building *b1=new building(func_1);
                building *b2=new building(func_2);
                building *b3=new building(func_3);
                if(percentile==1){
                    qreal w1=80;
                    qreal h1=(std::rand()%2==0)?13:23;
                    qreal w2=40+(std::rand()%5)*10;
                    qreal h2=(std::rand()%2==0)?18:28;
                    qreal w3=80;
                    qreal h3=(std::rand()%2==0)?13:23;
                    b1->setRect(-w1/2,-h1/2,w1,h1);
                    b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                    b1->setText(std::rand()%20+1);
                    b2->setRect(-w2/2,-h2/2,w2,h2);
                    b2->setPos(QPoint(x*100+w2/2,y*100+25+h2/2));
                    b2->setText(std::rand()%20+1);
                    b3->setRect(-w3/2,-h3/2,w3,h3);
                    b3->setPos(QPoint(x*100+w3/2,y*100+55+h3/2));
                    b3->setText(std::rand()%20+1);
                }else if(percentile==2){
                    qreal w1=30+(std::rand()%3)*10;
                    qreal h1=30+(std::rand()%3)*10;
                    qreal w2=30+(std::rand()%3)*10;
                    qreal h2=(std::rand()%2==0)?(76-h1):(66-h1);
                    qreal w_max=(w1>w2)?w1:w2;
                    qreal w3=(std::rand()%2==0)?(76-w_max):(66-w_max);
                    qreal h3=80;
                    b1->setRect(-w1/2,-h1/2,w1,h1);
                    b1->setText(std::rand()%20+1);
                    b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                    b2->setRect(-w2/2,-h2/2,w2,h2);
                    qreal y2=((h2-(66-h1))<0.01)?(y*100+h1+14+h2/2):(y*100+h1+h2/2+4);
                    b2->setPos(QPoint(x*100+w2/2,int(y2)));
                    b2->setText(std::rand()%20+1);
                    b3->setRect(-w3/2,-h3/2,w3,h3);
                    qreal x3=(w3-(66-w_max)<0.01)?(x*100+w_max+14+w3/2):(x*100+w_max+w3/2+4);
                    b3->setPos(QPoint(int(x3),y*100+h3/2));
                    b3->setText(std::rand()%20+1);
                }else if(percentile==3){
                    qreal w1=80;
                    qreal h1=30+(std::rand()%3)*10;
                    qreal w2=30+(std::rand()%3)*10;
                    qreal h2=(std::rand()%2==0)?(76-h1):(66-h1);
                    qreal w3=(std::rand()%2==0)?(76-w2):(66-w2);
                    qreal h3=(std::rand()%2==0)?(76-h1):(66-h1);
                    b1->setRect(-w1/2,-h1/2,w1,h1);
                    b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                    b2->setRect(-w2/2,-h2/2,w2,h2);
                    qreal y2=((h2-(66-h1))<0.01)?(y*100+h1+14+h2/2):(y*100+h1+4+h2/2);
                    b2->setPos(QPoint(x*100+w2/2,int(y2)));
                    b2->setText((std::rand()%20+1));
                    b3->setRect(-w3/2,-h3/2,w3,h3);
                    qreal x3=(w3-(66-w2)<0.01)?(x*100+w2+14+w3/2):(x*100+w2+w3/2+4);
                    qreal y3=((h3-(66-h1))<0.01)?(y*100+h1+14+h3/2):(y*100+h1+h3/2+4);
                    b3->setPos(QPoint(int(x3),int(y3)));
                    b3->setText((std::rand()%20+1));
                }
               scene->addItem(b1);
               scene->addItem(b2);
               scene->addItem(b3);
            }else if(percentile==4||percentile==5){
                publicspace::Function func_1;
                func_1=publicspace::Function(std::rand()%2);
                publicspace *p=new publicspace(func_1);
                building::Function func_2;
                func_2=building::Function(std::rand()%6);
                building *b1=new building(func_2);
                if(percentile==4){
                    qreal w1=30+(std::rand()%3)*10;
                    qreal h1=40+(std::rand()%3)*20;
                    qreal w2=70-w1;
                    qreal h2=(h1-80<0.01)?(40+(std::rand()%3)*20):80;
                    int random=std::rand()%2;
                    if(random==0){
                        p->setRect(-w1/2,-h1/2,w1,h1);
                        p->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                        b1->setRect(-w2/2,-h2/2,w2,h2);
                        b1->setPos(QPoint(x*100+w1+10+w2/2,y*100+h2/2));
                        b1->setText((std::rand()%20+1));
                    }else if(random==1){
                        b1->setRect(-w1/2,-h1/2,w1,h1);
                        b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                        b1->setText((std::rand()%20+1));
                        p->setRect(-w2/2,-h2/2,w2,h2);
                        p->setPos(QPoint(x*100+w1+10+w2/2,y*100+h2/2));
                    }
                 }else if(percentile==5){
                    qreal w1=40+(std::rand()%3)*20;
                    qreal h1=30+(std::rand()%3)*10;
                    qreal w2=(h1-80<0.01)?(40+(std::rand()%3)*20):80;
                    qreal h2=70-h1;
                    int random=std::rand()%2;
                    if(random==0){
                        p->setRect(-w1/2,-h1/2,w1,h1);
                        p->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                        b1->setRect(-w2/2,-h2/2,w2,h2);
                        b1->setPos(QPoint(x*100+w2/2,y*100+10+h1+h2/2));
                        b1->setText((std::rand()%20+1));
                    }else if(random==1){
                        b1->setRect(-w1/2,-h1/2,w1,h1);
                        b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                        b1->setText((std::rand()%20+1));
                        p->setRect(-w2/2,-h2/2,w2,h2);
                        p->setPos(QPoint(x*100+w2/2,y*100+10+h1+h2/2));
                    }
                  }
                  scene->addItem(p);
                  scene->addItem(b1);
                }else if(percentile==6){
                  building::Function func_1;
                  func_1=building::Function(std::rand()%6);
                  building::Function func_2;
                  func_2=building::Function(std::rand()%6);
                  building::Function func_3;
                  func_3=building::Function(std::rand()%6);
                  building::Function func_4;
                  func_4=building::Function(std::rand()%6);
                  building *b1=new building(func_1);
                  building *b2=new building(func_2);
                  building *b3=new building(func_3);
                  building *b4=new building(func_4);
                  qreal w1=30+(std::rand()%3)*10;
                  qreal h1=30+(std::rand()%3)*10;
                  qreal w2=w1-(std::rand()%2)*10;
                  qreal h2=(std::rand()%2==0)?(76-h1):(66-h1);
                  qreal w3=(std::rand()%2==0)?(76-w1):(66-w1);
                  qreal h3=h1+(std::rand()%2)*10;
                  qreal w4=(std::rand()%2==0)?(76-w2):(66-w2);
                  qreal h4=(std::rand()%2==0)?(76-h3):(66-h3);
                  b1->setRect(-w1/2,-h1/2,w1,h1);
                  b1->setText(std::rand()%20+1);
                  b1->setPos(QPoint(x*100+w1/2,y*100+h1/2));
                  b2->setRect(-w2/2,-h2/2,w2,h2);
                  qreal y2=((h2-(66-h1))<0.01)?(y*100+h1+14+h2/2):(y*100+h1+h2/2+4);
                  b2->setPos(QPoint(x*100+w2/2,int(y2)));
                  b2->setText(std::rand()%20+1);
                  b3->setRect(-w3/2,-h3/2,w3,h3);
                  qreal x3=(w3-(66-w1)<0.01)?(x*100+w1+14+w3/2):(x*100+w1+w3/2+4);
                  b3->setPos(QPoint(int(x3),y*100+h3/2));
                  b3->setText(std::rand()%20+1);
                  b4->setRect(-w4/2,-h4/2,w4,h4);
                  qreal x4=(w4-(66-w2)<0.01)?(x*100+w2+14+w4/2):(x*100+w2+w4/2+4);
                  qreal y4=((h4-(66-h3))<0.01)?(y*100+h3+14+h4/2):(y*100+h3+h4/2+4);
                  b4->setPos(QPoint(int(x4),int(y4)));
                  b4->setText(std::rand()%20+1);
                  scene->addItem(b1);
                  scene->addItem(b2);
                  scene->addItem(b3);
                  scene->addItem(b4);
            }
          }
     }
}

void cityscape::addBuilding(){
    block*bl=selectedBlock();
    building*b=new building;
    b->setRect(-20,-20,40,40);
    b->setLayer(1);
    b->setPos(bl->pos());
    scene->addItem(b);
}

void cityscape::addPublicSpace(){
    block*bl=selectedBlock();
    publicspace*p=new publicspace;
    p->setRect(-20,-20,40,40);
    p->setPos(bl->pos());
    scene->addItem(p);
}

void cityscape::toBuilding(){
    publicspace*p=selectedPublicSpace();
    building*b=new building;
    b->setRect(p->boundingRect());
    b->setPos(p->pos());
    scene->addItem(b);
    delete p;
}

void cityscape::toPublicSpace(){
    building*b=selectedBuilding();
    publicspace*p=new publicspace;
    p->setRect(b->boundingRect());
    p->setPos(b->pos());
    scene->addItem(p);
    delete b;
}

void cityscape::del()
{
    QList<QGraphicsItem*>items=scene->selectedItems();
    foreach(QGraphicsItem* str,items){
        block*bl=qgraphicsitem_cast<block*>(str);
        if(!bl)
          delete str;
    }
}

void cityscape::copyInfo(building*b,publicspace*p){
    if(!b&&!p)
        return;
    else if(b){
        QString str=QString("Building %1 %2 %3 %4")
                .arg(QString::number(b->boundingRect().width()))
                .arg(QString::number(b->boundingRect().height()))
                .arg(QString::number(b->getLayer()))
                .arg(QString::number(b->getFunction()));
        QApplication::clipboard()->setText(str);

    }else if(p){
        QString str=QString("Publicspace %1 %2 %3")
                .arg(QString::number(p->boundingRect().width()))
                .arg(QString::number(p->boundingRect().height()))
                .arg(QString::number(p->getFunction()));
        QApplication::clipboard()->setText(str);
    }
}

void cityscape::cut(){
    building*b=selectedBuilding();
    publicspace*p=selectedPublicSpace();
    copyInfo(b,p);
    delete b;
    delete p;
}

void cityscape::copy(){
    building*b=selectedBuilding();
    publicspace*p=selectedPublicSpace();
    copyInfo(b,p);
}

void cityscape::paste()
{
    block*bl=selectedBlock();
    QString str=QApplication::clipboard()->text();
    QStringList parts=str.split(" ");
    double width=parts[1].toDouble();
    double height=parts[2].toDouble();
    if(parts.first()=="Building"&&parts.count()>=5){
        building*b=new building(building::Function(parts[4].toInt()));
        b->setPos(bl->pos());
        b->setRect(-width/2,-height/2,width,height);
        b->setLayer(parts[3].toInt());
        scene->addItem(b);
    }else if(parts.first()=="Publicspace"&&parts.count()>=4){
        publicspace*p=new publicspace(publicspace::Function(parts[3].toInt()));
        p->setPos(bl->pos());
        p->setRect(-width/2,-height/2,width,height);
        scene->addItem(p);
    }
}

//problem:sometimes went wrong
void cityscape::combine(){
    BlockPair blocks=selectedBlockPair();
    block *b1=blocks.first;
    block *b2=blocks.second;
    qreal b1_x=b1->pos().x();
    qreal b1_y=b1->pos().y();
    qreal b2_x=b2->pos().x();
    qreal b2_y=b2->pos().y();
    if(b1_x-b2_x<0.01){
        qreal b3_w=b1->getWidth();
        qreal b3_h=abs(b2_y-b1_y)+(b1->getHeight()/2)+(b2->getHeight()/2);
        block *b3=new block(b3_w,b3_h);
        qreal y1=b1_y+b3_h/2-(b1->getHeight()/2);
        qreal y2=b2_y+b3_h/2-(b2->getHeight()/2);
        qreal b3_y=(y1<y2)?y1:y2;
        b3->setPos(QPointF(b1_x,b3_y));
        scene->addItem(b3);
        delete b1;
        delete b2;
    }else if(b1_y-b2_y<0.01){
        qreal b3_w=abs(b2_x-b1_x)+(b1->getWidth()/2)+(b2->getWidth()/2);
        qreal b3_h=b1->getHeight();
        block *b3=new block(b3_w,b3_h);
        qreal x1=b1_x-(b1->getWidth()/2)+b3_w/2;
        qreal x2=b2_x-(b2->getWidth()/2)+b3_w/2;
        qreal b3_x=(x1<x2)?x1:x2;
        b3->setPos(QPointF(b3_x,b1_y));
        scene->addItem(b3);
        delete b1;
        delete b2;
    }
}

void cityscape::divide_x(){
    block *b=selectedBlock();
    qreal h=b->getHeight();
    qreal w=b->getWidth();
    qreal x=b->pos().x();
    qreal y=b->pos().y();
    qreal w1=(w-7)/2;
    qreal w2=w1;
    block *b1=new block(w1,h);
    block *b2=new block(w2,h);
    b1->setPos(QPointF(x-3.5-w1/2,y));
    b2->setPos(QPointF(x+3.5+w2/2,y));
    scene->addItem(b1);
    scene->addItem(b2);
    delete b;
}

void cityscape::divide_y(){
    block *b=selectedBlock();
    qreal h=b->getHeight();
    qreal w=b->getWidth();
    qreal x=b->pos().x();
    qreal y=b->pos().y();
    qreal h1=(h-7)/2;
    qreal h2=h1;
    block *b1=new block(w,h1);
    block *b2=new block(w,h2);
    b1->setPos(QPointF(x,y-3.5-h1/2));
    b2->setPos(QPointF(x,y+3.5+h1/2));
    scene->addItem(b1);
    scene->addItem(b2);
    delete b;
}

void cityscape::properties(){
    building*b=selectedBuilding();
    block*bl=selectedBlock();
    publicspace*p=selectedPublicSpace();
    if(b){
      BuildingPropertiesDialog Bdialog(b);
      Bdialog.exec();
    }else if(bl){
      BlockPropertiesDialog Bldialog(bl);
      Bldialog.exec();
    }else if(p){
      PublicPropertiesDialog Pdialog(p);
      Pdialog.exec();
    }
}

void cityscape::updateActions(){
    bool hasSelection=!scene->selectedItems().isEmpty();
    bool isBlock=(selectedBlock());
    bool isBlockPair=(selectedBlockPair()!=BlockPair());
    bool isBuilding=(selectedBuilding());
    bool isPublicSpace=(selectedPublicSpace());
    addBuildingAction->setEnabled(isBlock);
    addPublicSpaceAction->setEnabled(isBlock);
    toPublicSpaceAction->setEnabled(isBuilding);
    toBuildingAction->setEnabled(isPublicSpace);
    cutAction->setEnabled(isPublicSpace||isBuilding);
    copyAction->setEnabled(isPublicSpace||isBuilding);
    pasteAction->setEnabled(isBlock);
    deleteAction->setEnabled(hasSelection);
    combineAction->setEnabled(isBlockPair);
    xdivideAction->setEnabled(isBlock&&selectedBlock()->getWidth()>=50);
    ydivideAction->setEnabled(isBlock&&selectedBlock()->getHeight()>=50);
    propertiesAction->setEnabled(isBuilding||isBlock||isPublicSpace);

    foreach(QAction*action,view->actions())
           view->removeAction(action);
       foreach(QAction*action,editMenu->actions()){
           if(action->isEnabled())
               view->addAction(action);
    }
}

void cityscape::createActions(){
    exitAction=new QAction(tr("E&xit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    addBuildingAction=new QAction(tr("&Building"),this);
    addBuildingAction->setIcon(QIcon("..\\images\\residential.png"));
    addBuildingAction->setShortcut(tr("Ctrl+B"));
    connect(addBuildingAction,SIGNAL(triggered()),this,SLOT(addBuilding()));

    addPublicSpaceAction=new QAction(tr("&PublicSpace"),this);
    addPublicSpaceAction->setIcon(QIcon("..\\images\\park.png"));
    addPublicSpaceAction->setShortcut(tr("Ctrl+P"));
    connect(addPublicSpaceAction,SIGNAL(triggered()),this,SLOT(addPublicSpace()));

    toBuildingAction=new QAction(tr("toBuilding"),this);
    toBuildingAction->setIcon(QIcon("..\\images\\tobuilding.png"));
    toBuildingAction->setShortcut(tr("Shift+B"));
    connect(toBuildingAction,SIGNAL(triggered()),this,SLOT(toBuilding()));

    toPublicSpaceAction=new QAction(tr("toPublicSpace"),this);
    toPublicSpaceAction->setIcon(QIcon("..\\images\\topark.png"));
    toPublicSpaceAction->setShortcut(tr("Shift+P"));
    connect(toPublicSpaceAction,SIGNAL(triggered()),this,SLOT(toPublicSpace()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon("..\\images\\cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon("..\\images\\copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon("..\\images\\paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon("..\\images\\delete.png"));
    deleteAction->setShortcut(tr("Del"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

    //change later
    combineAction=new QAction(tr("C&ombine"),this);
    combineAction->setIcon(QIcon("..\\images\\combine.png"));
    combineAction->setShortcut(tr("Ctrl+O"));
    connect(combineAction,SIGNAL(triggered()),this,SLOT(combine()));

    //change later
    xdivideAction=new QAction(tr("&XDivide"),this);
    xdivideAction->setIcon(QIcon("..\\images\\xdivide.png"));
    xdivideAction->setShortcut(tr("Ctrl+X"));
    connect(xdivideAction,SIGNAL(triggered()),this,SLOT(divide_x()));

    //change later
    ydivideAction=new QAction(tr("&YDivide"),this);
    ydivideAction->setIcon(QIcon("..\\images\\ydivide.png"));
    ydivideAction->setShortcut(tr("Ctrl+Y"));
    connect(ydivideAction,SIGNAL(triggered()),this,SLOT(divide_y()));


    propertiesAction = new QAction(tr("P&roperties..."), this);
    connect(propertiesAction, SIGNAL(triggered()),this, SLOT(properties()));
}

void cityscape::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    editMenu=menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addBuildingAction);
    editMenu->addAction(addPublicSpaceAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(toBuildingAction);
    editMenu->addAction(toPublicSpaceAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(combineAction);
    editMenu->addAction(xdivideAction);
    editMenu->addAction(ydivideAction);
    editMenu->addSeparator();
    editMenu->addAction(propertiesAction);

    viewMenu=menuBar()->addMenu(tr("&View"));
}

void cityscape::createToolBars(){
    editToolBar=addToolBar(tr("Edit"));
    editToolBar->addAction(addBuildingAction);
    editToolBar->addAction(addPublicSpaceAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(toBuildingAction);
    editToolBar->addAction(toPublicSpaceAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(combineAction);
    editToolBar->addAction(xdivideAction);
    editToolBar->addAction(ydivideAction);
}

void cityscape::createDockWindows(){
    QDockWidget*dock=new QDockWidget(tr("Legends"),this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    colorlegends=new legends(dock);
    dock->setWidget(colorlegends);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock=new QDockWidget(tr("Index"),this);
    totalindex=new index(dock);
    dock->setWidget(totalindex);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock=new QDockWidget(tr("User"),this);
    userinformation=new user(dock);
    dock->setWidget(userinformation);
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());
}

publicspace*cityscape::selectedPublicSpace()const{
   QList<QGraphicsItem*>items=scene->selectedItems();
        if(items.count()==1){
            return qgraphicsitem_cast<publicspace*>(items.first());
                  }else{
         return 0;
         }
}

building*cityscape::selectedBuilding()const{
    QList<QGraphicsItem*>items=scene->selectedItems();
         if(items.count()==1){
             return qgraphicsitem_cast<building*>(items.first());
                   }else{
             return 0;
          }
}

block*cityscape::selectedBlock() const{
    QList<QGraphicsItem*>items=scene->selectedItems();
         if(items.count()==1){
             return qgraphicsitem_cast<block*>(items.first());
                   }else{
             return 0;
          }
}

cityscape::BlockPair cityscape::selectedBlockPair()const{
    QList<QGraphicsItem*>items=scene->selectedItems();
         if(items.count()==2){
             block*first=qgraphicsitem_cast<block*>(items.first());
             block*second=qgraphicsitem_cast<block*>(items.last());
             if(first&&second){
                 qreal f_x=first->pos().x();
                 qreal f_y=first->pos().y();
                 qreal s_x=second->pos().x();
                 qreal s_y=second->pos().y();
                 if(((f_x-s_x)<0.01&&(first->getWidth()-second->getWidth())<0.01&&
                         abs(f_y-s_y)-(first->getHeight()/2)-(second->getHeight()/2)<30)
                         ||((s_y-f_y)<0.01&&(first->getHeight()-second->getHeight())<0.01&&
                            abs(f_x-s_x)-(first->getWidth()/2)-(second->getWidth()/2)<30))
                 {
                     return BlockPair(first,second);
                 }

             }
         }
         return BlockPair();
}


