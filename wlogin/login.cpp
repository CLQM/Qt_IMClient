#include "login.h"
#include "ui_login.h"

#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::setIDPassword(QString id, QString pswd)
{
    ui->le_id->setText(id);
    ui->le_pswd->setText(pswd);
}

void Login::on_pb_enter_clicked()
{//登录
    emit signalConnectServer(ui->le_id->text(),ui->le_pswd->text());
    qDebug() << "登录";
}

void Login::on_pb_register_clicked()
{//注册
    emit signalRegister();
}

void Login::on_pb_cancel_clicked()
{//取消
    this->close();
}
