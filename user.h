#ifndef USER_H
#define USER_H

#include <QWidget>
#include "ui_user.h"

class user:public QWidget,private Ui::user
{
public:
    user(QWidget*parent=nullptr);
private slots:
    void on_buttonBox_accepted();
private:
    QString nickname;
    QString gender;
    int age;
    QString job;
    QString remark;
};

#endif // USER_H
