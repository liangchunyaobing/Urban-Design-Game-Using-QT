#ifndef PUBLICPROPERTIESDIALOG_H
#define PUBLICPROPERTIESDIALOG_H

#include "ui_PublicPropertiesDialog.h"
#include "publicspace.h"

class PublicPropertiesDialog:public QDialog,private Ui::PublicPropertiesDialog{
    Q_OBJECT
public:
    PublicPropertiesDialog(publicspace*p,QWidget*parent=nullptr);
private slots:
    void on_buttonBox_accepted();
private:
    publicspace*p;
};

#endif // PUBLICPROPERTIESDIALOG_H
