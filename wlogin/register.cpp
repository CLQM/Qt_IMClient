#include "register.h"
#include "ui_register.h"

#include <QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pb_enter_clicked()
{//注册帐号
    if(ui->le_pswd->text() == ui->le_rpswd->text())
    {
        emit signalRegisterAsk(ui->le_nickName->text(),ui->le_pswd->text());
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("ERROR:Two different input");  //显示内容
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);    //显示的按键
        msgBox.setDefaultButton(QMessageBox::Retry);

        int ret = msgBox.exec();//生成对话框
        switch(ret){
        case QMessageBox::Retry :
            ui->le_nickName->setFocus();//输入首选项
            msgBox.close();
            break;
        case QMessageBox::Cancel :
            ui->le_nickName->setFocus();
            break;
        default:
            break;
        }
    }
}

void Register::on_pb_cancel_clicked()
{
    emit signalRegisterCancel();
}
