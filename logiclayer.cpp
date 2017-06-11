#include "logiclayer.h"
#include <QDebug>

UserInfo *LogicLayer::m_userInfo = new UserInfo;
List_FriendInfo *LogicLayer::m_friendInfoList = new List_FriendInfo;
List_CrowdInfo *LogicLayer::m_crowdInfoList = new List_CrowdInfo;
//FriendList *LogicLayer::m_friendList = new FriendList;

LogicLayer::LogicLayer(QObject *parent) : QObject(parent)
{//view和database连接
    m_register = new Register;
    m_login = new Login();
    m_friendList = new FriendList;
    m_userInfoFrom = new UserInfoForm;
    m_formAddFriend = new AddFriend();

    m_connectServer = new ConnectServer(this);  //this可以让本程序结束时，TCP连接断开

    connect(m_login, SIGNAL(signalRegister()),
                this, SLOT(slotRegister()));    //点击了register
    connect(m_register,SIGNAL(signalRegisterCancel()),
            this,SLOT(slotRegisterCancel()));   //点击了cancel
    connect(m_register,SIGNAL(signalRegisterAsk(QString,QString)),
            m_connectServer,SLOT(slotRegisterAsk(QString,QString)));//点击了register.enter
    connect(m_login,SIGNAL(signalConnectServer(QString,QString)),
            m_connectServer,SLOT(slotConnectServer(QString,QString)));//login.enter
    connect(this,SIGNAL(signalGetUserCrowdList(UserInfo*)),
            m_connectServer, SLOT(slotGetUserCrowdList(UserInfo*)));

//    connect(m_userInfoFrom,SIGNAL(signalSaveUserEdit(QString,QString,QString)),
//            m_connectServer,SLOT(slotSaveUserEdit(QString,QString,QString)));

    m_login->show();
}

void LogicLayer::slotUserLoginSuccess(UserInfo * info)
{//登录成功
    m_login->hide();
    m_friendList->initUserInfo(info);   //显示用户名
    m_friendList->show();
//    info->printInfos();

    connect(m_friendList,SIGNAL(signalClickUserInfo(UserInfo*)),
            this,SLOT(slotClickUserInfo(UserInfo*)));
    connect(m_friendList,SIGNAL(signalFindFriend()),this,SLOT(slotFindFriend()));

}

void LogicLayer::slotClickUserInfo(UserInfo *info)
{//在界面中显示当前用户的一部分信息
    m_userInfoFrom->show();
    m_userInfoFrom->updateUserInfoToForm(info);
}

void LogicLayer::slotUserRegisterSuccess(UserInfo *info)
{
    m_register->hide(); //注册界面隐藏
    m_login->setIDPassword(     //将注册到的uid显示到登录界面
                info->getUID(), info->getRPassword());
    m_login->show();
}

void LogicLayer::slotRegister()
{//界面转换
    m_register->show();
    m_login->hide();
}

void LogicLayer::slotRegisterCancel()
{//界面转换
    m_login->show();
    m_register->close();
}

void LogicLayer::slotFindFriend()
{//添加好友
    connect(m_formAddFriend,SIGNAL(signalFindFriend(QString)),
            m_connectServer,SLOT(slotFindFriend(QString)));
    connect(m_formAddFriend,SIGNAL(signalAddFriend(QString)),
            m_connectServer,SLOT(slotAddFriend(QString)));
    connect(m_formAddFriend,SIGNAL(signalAddFriendCancel()),
            this,SLOT(slotAddFriendCancel()));
    m_formAddFriend->show();
}

void LogicLayer::slotAddFriendCancel(void)
{
    m_formAddFriend->close();
}

void LogicLayer::UserInfoEditSuccess(UserInfo *info)
{
    m_userInfo = info;
    m_friendList->close();
    m_friendList = new FriendList;
    m_friendList->show();
}

void LogicLayer::slotUpdateFriendList(void)
{
    m_friendList->updateFriendList();
    emit signalGetUserCrowdList(m_userInfo);
}

void LogicLayer::slotUserFindFriendSuccess(UserInfo *info)
{
    m_formAddFriend->updateSearchResult(info);
}

void LogicLayer::slotUpdateCrowdList(void)
{//群列表
    m_friendList->updateCrowdList();
}
