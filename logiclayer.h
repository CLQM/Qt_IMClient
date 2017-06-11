#ifndef LOGICLAYER_H
#define LOGICLAYER_H
//=============逻辑层

#include <QObject>
#include "login.h"
#include "connectserver.h"
#include "register.h"
#include "friendlist.h"
#include "common.h"
#include "friendinfo.h"
#include "userinfoform.h"
#include "addfriend.h"
#include "crowdinfo.h"

class ConnectServer;
class FriendList;

class LogicLayer : public QObject
{
    Q_OBJECT
signals:
    void signalGetUserCrowdList(UserInfo *info);

public slots:
    void slotRegister();
    void slotRegisterCancel();
    void slotUserLoginSuccess(UserInfo *info);
    void slotUserRegisterSuccess(UserInfo *info);
    void slotClickUserInfo(UserInfo *info);
    void slotUpdateFriendList(void);
    void slotUpdateCrowdList(void);
    void slotUserFindFriendSuccess(UserInfo *info);
    void slotFindFriend(void);
    void slotAddFriendCancel(void);

public:
    explicit LogicLayer(QObject *parent = 0);
    static UserInfo *m_userInfo;
    static List_FriendInfo *m_friendInfoList;
    static List_CrowdInfo *m_crowdInfoList;
//    static FriendList *m_friendList;

    void UserInfoEditSuccess(UserInfo *info);



private:
    Login *m_login;
    ConnectServer *m_connectServer;
    Register *m_register;

    AddFriend *m_formAddFriend;
    FriendList *m_friendList;
    UserInfoForm *m_userInfoFrom;
};

#endif // LOGICLAYER_H
