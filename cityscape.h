#ifndef CITYSCAPE_H
#define CITYSCAPE_H

#include<QMainWindow>

#include "block.h"
#include "publicspace.h"
#include "building.h"
#include "index.h"
#include "legends.h"
#include "user.h"

class CityView;

class cityscape:public QMainWindow{
    Q_OBJECT
public:
    //类型别名
    typedef QPair<block*,block*>BlockPair;
    cityscape();
private slots:
    void addBuilding();
    void addPublicSpace();
    void del();
    void toPublicSpace();
    void toBuilding();
    void cut();
    void copy();
    void paste();
    void combine();
    void divide_x();
    void divide_y();
    void properties();
    void updateActions();

private:
    void generateCityBlocks();
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();
    publicspace*selectedPublicSpace()const;
    building*selectedBuilding()const;
    block*selectedBlock() const;
    void copyInfo(building*b,publicspace*p);
    BlockPair selectedBlockPair()const;

    QMenu*fileMenu;
    QMenu*editMenu;
    QMenu*viewMenu;
    QToolBar*editToolBar;
    QAction*exitAction;
    QAction*addPublicSpaceAction;
    QAction*addBuildingAction;
    QAction*toPublicSpaceAction;
    QAction*toBuildingAction;
    QAction*cutAction;
    QAction*copyAction;
    QAction*pasteAction;
    QAction*deleteAction;
    QAction*combineAction;
    QAction*xdivideAction;
    QAction*ydivideAction;
    QAction*propertiesAction;

    legends*colorlegends;
    index*totalindex;
    user*userinformation;
    QGraphicsScene *scene;
    CityView*view;
};

#endif // CITYSCAPE_H
