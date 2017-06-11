#include "groupchatting.h"
#include "ui_groupchatting.h"

GroupChatting::GroupChatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChatting)
{
    ui->setupUi(this);
}

GroupChatting::~GroupChatting()
{
    delete ui;
}
