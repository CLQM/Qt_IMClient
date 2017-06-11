#include "userinfoformedit.h"
#include "ui_userinfoformedit.h"

UserInfoFormEdit::UserInfoFormEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoFormEdit)
{
    ui->setupUi(this);
    /*使显示内容可修改*/
    ui->le_name->setReadOnly(true);
    ui->le_sign->setReadOnly(true);
    ui->le_birth->setReadOnly(true);
    ui->le_sex->setReadOnly(true);
    ui->le_netAge->setReadOnly(true);
}

UserInfoFormEdit::~UserInfoFormEdit()
{
    delete ui;
}

void UserInfoFormEdit::slotUserEditAsk()
{
    this->show();
}
