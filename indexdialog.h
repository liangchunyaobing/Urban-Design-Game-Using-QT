#ifndef INDEXDIALOG_H
#define INDEXDIALOG_H

#include "ui_IndexDialog.h"

class IndexDialog:public QDialog,private Ui::IndexDialog{
    Q_OBJECT
public:
    IndexDialog(QWidget*parent=nullptr);
private slots:
    void on_buttonBox_accepted();

};

#endif // INDEXDIALOG_H
