#include "friendlist.h"
#include "ui_friendlist.h"

#include <QDebug>
#include <QString>

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);

    m_info = new UserInfo;  //当前登录用户
    m_listenClientChat = new ConnectClient();
    m_modelFriendList = new ModelFriendInfoStatu();
    m_modelCrowdList = new ModelCrowdInfoStatu();
}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::on_pb_name_clicked()
{

    emit signalClickUserInfo(m_info);
}

void FriendList::on_pb_addFriend_clicked()
{
    emit signalFindFriend();
}

void FriendList::initUserInfo(UserInfo *info)
{
    m_info->updataUserinfo(info);//name
    ui->pb_name->setText(info->getRName());
    this->setWindowTitle("WeChat");
}

void FriendList::updateFriendList(void)
{
    ui->tv_friendlist->setModel(m_modelFriendList);
}

void FriendList::updateCrowdList(void)
{
    ui->tv_crowdlist->setModel(m_modelCrowdList);
}

void FriendList::on_tv_friendlist_doubleClicked(const QModelIndex &index)
{//双击显示聊天界面
    m_priChatForm = new FormChatting;
    connect(m_priChatForm,SIGNAL(signalSendMessage(QString,QString)),
            m_listenClientChat,SLOT(slotSendMessage(QString,QString)));
    QString UID = m_modelFriendList->data(
                m_modelFriendList->index(index.row(),0),0).toString();
    for(int i = 0; i < LogicLayer::m_friendInfoList->size(); i++)
    {
        if(LogicLayer::m_friendInfoList->at(i).getUID() == UID)
        {
            m_priChatForm->updateFormFriendInfo(LogicLayer::m_friendInfoList->at(i));
            break;
        }
    }
    ModelFriendInfoStatu::m_mapPriChatForm.insert(
                UID.toInt(), m_priChatForm);
    m_priChatForm->show();
}



void FriendList::on_tv_crowdlist_doubleClicked(const QModelIndex &index)
{//双击群聊界面
    m_crowdChat = new CrowdChatting;
    connect(m_crowdChat,SIGNAL(signalSendMessage(QString,QString)),
            m_listenClientChat,SLOT(slotSendCrowdMessage(QString,QString)));
    QString CID = m_modelCrowdList->data(m_modelCrowdList->index(index.row(),0),0).toString();
    for(int i = 0; i < LogicLayer::m_crowdInfoList->size(); i++)
    {
        if(LogicLayer::m_crowdInfoList->at(i).getCID() == CID)
        {
            m_crowdChat->updateFormCrowdInfo(LogicLayer::m_crowdInfoList->at(i));
            break;
        }
    }
    ModelCrowdInfoStatu::m_mapPriChatForm.insert(
                CID.toInt(),m_crowdChat);

    m_crowdChat->show();
}
