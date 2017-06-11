#include "addfriend.h"
#include "ui_addfriend.h"

#include <QDebug>

AddFriend::AddFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    m_info = new UserInfo;
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_pb_search_clicked()
{
    emit signalFindFriend(ui->le_seachuid->text());
    qDebug() << ui->le_seachuid->text();
}

void AddFriend::on_pb_add_clicked()
{
    emit signalAddFriend(m_info->getUID());
}

void AddFriend::on_pb_cancle_clicked()
{
    emit signalAddFriendCancel();
}

void AddFriend::updateSearchResult(UserInfo *info)
{
    m_info->updataUserinfo(info);
    ui->le_name->setText(m_info->getRName());
    ui->le_uid->setText(m_info->getUID());
    ui->le_sign->setText(m_info->getSelfSign());
}
