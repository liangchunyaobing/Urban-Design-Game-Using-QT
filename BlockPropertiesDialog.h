#ifndef BLOCKPROPERTIESDIALOG_H
#define BLOCKPROPERTIESDIALOG_H

#include "ui_BlockPropertiesDialog.h"
#include "block.h"

class BlockPropertiesDialog:public QDialog,private Ui::BlockPropertiesDialog{
    Q_OBJECT
public:
    BlockPropertiesDialog(block*bl,QWidget*parent=nullptr);
private slots:
    void on_buttonBox_accepted();
private:
    block*bl;
};

#endif // BLOCKPROPERTIESDIALOG_H
