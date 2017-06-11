#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include "common.h"
#include "modelfriendinfostatu.h"
#include "connectclient.h"
#include "modelcrowdinfostatu.h"

#include <QWidget>

class ConnectClient;

namespace Ui {
class FriendList;
}

class FriendList : public QWidget
{
    Q_OBJECT
signals:
    void signalClickUserInfo(UserInfo *info);
    void signalFindFriend(void);

private slots:
    void on_pb_name_clicked();

    void on_pb_addFriend_clicked();

    void on_tv_friendlist_doubleClicked(const QModelIndex &index);

    void on_tv_crowdlist_doubleClicked(const QModelIndex &index);

public:
    explicit FriendList(QWidget *parent = 0);
    ~FriendList();

    void initUserInfo(UserInfo *info);
    void updateFriendList(void);
    void updateCrowdList(void);



private:
    Ui::FriendList *ui;

    UserInfo *m_info;
    FormChatting *m_priChatForm;
    CrowdChatting *m_crowdChat;
    ConnectClient *m_listenClientChat;
    ModelFriendInfoStatu *m_modelFriendList;
    ModelCrowdInfoStatu *m_modelCrowdList;
};

#endif // FRIENDLIST_H
