#include "user.h"

user::user(QWidget*parent)
    :QWidget(parent)
{
    setupUi(this);
    nickname="(no more than 10 letters)";
    NameEdit->setText(nickname);
    gender="Secret";
    GendercomboBox->setCurrentText(gender);
    age=0;
    AgespinBox->setValue(age);
    job="Secret";
    JobcomboBox->setCurrentText(job);
    remark="(no more than 100 words)";
    remarksEdit->setText(remark);
}

void user::on_buttonBox_accepted(){
    nickname=NameEdit->text();
    gender=GendercomboBox->currentText();
    age=AgespinBox->value();
    job=JobcomboBox->currentText();
    remark=remarksEdit->toPlainText();
}
