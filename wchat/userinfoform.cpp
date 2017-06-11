#include "userinfoform.h"
#include "ui_userinfoform.h"

#include <QDebug>

UserInfo *UserInfoForm::m_userInfo = new UserInfo;

UserInfoForm::UserInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoForm)
{
    ui->setupUi(this);
}

UserInfoForm::~UserInfoForm()
{
    delete ui;
}

void UserInfoForm::updateUserInfoToForm(UserInfo *info)
{
    ui->le_name->setText(info->getRName());
    qDebug() << info->getRName();
    ui->le_uid->setText(info->getUID());
    ui->le_sign->setText(info->getSelfSign());
    ui->pb_Save->setEnabled(false);
    m_userInfo = info;
}

void UserInfoForm::on_pb_Edit_clicked()
{//隐藏本界面
    ui->le_name->setEnabled(true);
    ui->le_sign->setEnabled(true);
    ui->pb_Save->setEnabled(true);
    ui->pb_Edit->setEnabled(false);
}

void UserInfoForm::on_pb_Save_clicked()
{
    ui->le_name->setText(ui->le_name->text());
    ui->le_sign->setText(ui->le_sign->text());
    ui->le_name->setEnabled(false);
    ui->le_sign->setEnabled(false);
    ui->pb_Save->setEnabled(false);
    ui->pb_Edit->setEnabled(true);

//    emit signalSaveUserEdit(m_userInfo->getUID(),ui->le_name->text(),ui->le_sign->text());
}
