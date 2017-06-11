#include "execusercmd.h"
#include <QDebug>
#include <QStringList>

#include "common.h"
#include "logiclayer.h"
#include <QMessageBox>
#include "modelfriendinfostatu.h"
#include <QString>

ExecUserCmd::ExecUserCmd()
{
    m_imProtocol = new IMProtocol;
}

ExecUserCmd::~ExecUserCmd()
{
    delete m_imProtocol;
}

void ExecUserCmd::analysisProtocol(IMProtocol *protocol)
{
//    qDebug() << "analysisProtocol";
    m_imProtocol->updataMsg(protocol);
//    m_imProtocol->printMsgInfo();

    execErrorInfo();
}

///
/// \brief ExecUserCmd::execErrorInfo
///
void ExecUserCmd::execErrorInfo(void)
{
//    qDebug() << "execErrorInfo";
    switch (m_imProtocol->getErrorInfo()) {
    case ERROR_INFO_NONE: execUserOperate(); break;
    case ERROR_INFO_DATA: break;
    case ERROR_INFO_BUSY: break;
    case ERROR_INFO_NETWORK: break;
    default: break;
    }
}

///
/// \brief ExecUserCmd::execUserOperate
///
void ExecUserCmd::execUserOperate(void)
{
//    qDebug() << "execUserOperate";
    switch (m_imProtocol->getUserOperate()) {
    case USER_OPE_NONE: break;
    case USER_OPE_LOGIN: execOperateCmdLogin(); break;
    case USER_OPE_USER: execOperateCmdUser(); break;
    case USER_OPE_FRIEND: execOperateCmdFriend(); break;
    case USER_OPE_CROWD: execOperateCmdCrowd(); break;
    case USER_OPE_CHAT: execOperateCmdChat(); break;
    case USER_OPE_MOOD: execOperateCmdMood(); break;
    default: break;
    }
}

///
/// \brief ExecUserCmd::execOperateCmdLogin
///
void ExecUserCmd::execOperateCmdLogin(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_LOGIN_ASK: execOperateCmdLoginAsk(); break;
    case OPE_CMD_EXIT_ASK: execOperateCmdExitAsk(); break;
    case OPE_CMD_REGISTER_ASK: execOperateCmdRegisterAsk(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdLoginAsk(void)
{
    QStringList list = m_imProtocol->getDataContent().split("|");

    UserInfo *info = new UserInfo;
    info->updataRegisterinfo(list[0], list[1], list[2], list[3]);
    info->updataIpAddrinfo(list[4], list[5], list[6]);
    info->updataUserinfo(list[7], list[8]);

    LogicLayer::m_userInfo->updataUserinfo(info);
    emit signalUserLoginSuccess(info);
//    emit signalUserLoginCrowdSuccess(info);
}

void ExecUserCmd::execOperateCmdExitAsk(void)
{

}

void ExecUserCmd::execOperateCmdRegisterAsk(void)
{
    QStringList list = m_imProtocol->getDataContent().split("|");

    UserInfo *info = new UserInfo;
    info->updataRegisterinfo(list[0], list[1], list[2], list[3]);
    info->updataIpAddrinfo(list[4], list[5], list[6]);
    info->updataUserinfo(list[7], list[8]);

    emit signalUserRegisterSuccess(info);
}

///
/// \brief ExecUserCmd::execOperateCmdUser
///
void ExecUserCmd::execOperateCmdUser(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_USER_ASK: execOperateCmdUserAsk(); break;
    case OPE_CMD_USER_DELETE: execOperateCmdUserUpdate(); break;
    case OPE_CMD_USER_UPDATE: execOperateCmdUserDelete(); break;
    case OPE_CMD_USER_CROWD_ASK: execOperateCmdUserCrowdAsk();break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdUserCrowdAsk(void)
{
    CrowdInfo info;
    QStringList crowdInfoList = m_imProtocol->getDataContent().split("^^");
    for(int i = 0; i < crowdInfoList.size() - 1; i++)
    {
//        qDebug() << crowdInfoList.at(i);
        info.unpackageinfos(crowdInfoList.at(i));
        LogicLayer::m_crowdInfoList->append(info);
    }
    emit signalUpdateCrowdList();
}

void ExecUserCmd::execOperateCmdUserAsk(void)
{
    FriendInfo info;
    QStringList friendInfoList = m_imProtocol->getDataContent().split("^^");
    for(int i = 0; i < friendInfoList.size() - 1; i++)
    {
        info.unpackageinfos(friendInfoList.at(i));
        LogicLayer::m_friendInfoList->append(info);
    }

    emit signalUpdateFriendList();
}

void ExecUserCmd::execOperateCmdUserUpdate(void)
{

}

void ExecUserCmd::execOperateCmdUserDelete(void)
{

}

///
/// \brief ExecUserCmd::execOperateCmdFriend
///
void ExecUserCmd::execOperateCmdFriend(void)
{
    qDebug() << "execOperateCmdFriend";
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_FRIEND_ADD: execOperateCmdFriendAdd(); break;
    case OPE_CMD_FRIEND_ASK: execOperateCmdFriendAsk(); break;
    case OPE_CMD_FRIEND_DEL: execOperateCmdFriendDel(); break;
    case OPE_CMD_FRIEND_FIND: execOperateCmdFriendFind(); break;
    case OPE_CMD_FRIEND_REMARK: execOperateCmdFriendRemark(); break;
    case OPE_CMD_GROUP_ADD: execOperateCmdGroupAdd(); break;
    case OPE_CMD_GROUP_MODIFY: execOperateCmdGroupModify(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdFriendAsk(void)
{
    QStringList list = m_imProtocol->getDataContent().split("|");

    UserInfo *info = new UserInfo;
    info->updataRegisterinfo(list[0], list[1], list[2], list[3]);
    info->updataIpAddrinfo(list[4], list[5], list[6]);
    info->updataUserinfo(list[7], list[8]);//6

    QMessageBox msgBox;
    msgBox.setText(tr("%1 want add you").arg(info->getRName()));
    msgBox.setInformativeText(tr("Do you want to add he?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    switch (msgBox.exec()) {
    case QMessageBox::Ok:
    /*添加者  被添加者*/
    {//同意添加
        QString msg =
                info->getUID() + "|" +LogicLayer::m_userInfo->getUID();
        qDebug() << info->getUID() + "|" + LogicLayer::m_userInfo->getUID();//6 |
        QByteArray *buffer =
                m_imProtocol->updataMsg(0, ERROR_INFO_NONE,
                                      USER_OPE_FRIEND, OPE_CMD_FRIEND_ADD,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      MSG_DATA_LENGTH_NONE, msg);

        emit signalSendMsgtoServer(buffer);
    }
    break;
    case QMessageBox::Cancel:
        msgBox.close();
        break;
    default:break;
    }
}

void ExecUserCmd::execOperateCmdFriendFind(void)
{
    qDebug() << "execOperateCmdFriendFind";
    QStringList list = m_imProtocol->getDataContent().split("|");

    UserInfo *info = new UserInfo;
    info->updataRegisterinfo(list[0], list[1], list[2], list[3]);
    info->updataIpAddrinfo(list[4], list[5], list[6]);
    info->updataUserinfo(list[7], list[8]);

    emit signalUserFindFriendSuccess(info);
}

void ExecUserCmd::execOperateCmdFriendAdd(void)
{

}

void ExecUserCmd::execOperateCmdFriendDel(void)
{

}

void ExecUserCmd::execOperateCmdFriendRemark(void)
{

}

void ExecUserCmd::execOperateCmdGroupAdd(void)
{

}

void ExecUserCmd::execOperateCmdGroupModify(void)
{

}

///
/// \brief execOperateCmdCrowd
///
void ExecUserCmd::execOperateCmdCrowd(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_CROWD_ASK: execOperateCmdCrowdAsk(); break;
    case OPE_CMD_CROWD_UPDATE: execOperateCmdCrowdUpdate(); break;
    case OPE_CMD_CROWD_DEL: execOperateCmdCrowdDel(); break;
    case OPE_CMD_CROWD_ADD: execOperateCmdCrowdAdd(); break;
    case OPE_CMD_MEMBER_ADD: execOperateCmdMemberAdd(); break;
    case OPE_CMD_MEMBER_DEL: execOperateCmdMemberDel(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdCrowdAsk(void)
{

}

void ExecUserCmd::execOperateCmdCrowdUpdate(void)
{

}

void ExecUserCmd::execOperateCmdCrowdDel(void)
{

}

void ExecUserCmd::execOperateCmdCrowdAdd(void)
{

}

void ExecUserCmd::execOperateCmdMemberAdd(void)
{

}

void ExecUserCmd::execOperateCmdMemberDel(void)
{

}

///
/// \brief execOperateCmdChat
///
void ExecUserCmd::execOperateCmdChat(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_CHAT_PRIVATE: execOperateCmdChatPrivate(); break;
    case OPE_CMD_CHAT_CROWD: execOperateCmdChatCrowd(); break;
    case OPE_CMD_CHAT_RECALL: execOperateCmdChatRecall(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdChatPrivate(void)
{
    quint16 recvHost = m_imProtocol->getRecvHost();
    quint16 sendHost = m_imProtocol->getSendHost();

    //本地接收到聊天数据
    if(LogicLayer::m_userInfo->getUID().toInt() == sendHost)
    {
        if(ModelFriendInfoStatu::m_mapPriChatForm.contains(recvHost))
        {
            ModelFriendInfoStatu::m_mapPriChatForm[recvHost]->slotPrivateChatWithFriend(
                    LogicLayer::m_userInfo->getRName(), m_imProtocol->getDataContent());
        }
    }

    //好友接收到聊天数据
    if(LogicLayer::m_userInfo->getUID().toInt() == recvHost)
    {
        if(ModelFriendInfoStatu::m_mapPriChatForm.contains(sendHost))
        {
            QString nickname;
            for(int i = 0; i < LogicLayer::m_friendInfoList->size(); i++)
            {
                if(LogicLayer::m_friendInfoList->at(i).getUID().toInt() == sendHost)
                {
                    nickname = LogicLayer::m_friendInfoList->at(i).getRName();
                }
            }
            ModelFriendInfoStatu::m_mapPriChatForm[sendHost]->slotPrivateChatWithFriend(
                        nickname, m_imProtocol->getDataContent());
        }else
        {
            ModelFriendInfoStatu::m_mapPriChatRecordNumber[sendHost]++;
            ModelFriendInfoStatu::m_multiMapPriChatRecord.insert(sendHost, m_imProtocol->getDataContent());
        }
    }
}

void ExecUserCmd::execOperateCmdChatCrowd(void)
{//群聊信息解析
    quint16 cidHost = m_imProtocol->getRecvHost();
    quint16 sendHost = m_imProtocol->getSendHost();

    //发生者udp接到自己的信息
    if(LogicLayer::m_userInfo->getUID().toInt() == sendHost)
    {
        if(ModelCrowdInfoStatu::m_mapPriChatForm.contains(cidHost))
        {
            ModelCrowdInfoStatu::m_mapPriChatForm[cidHost]->slotCrowdChatWithAll(
                                LogicLayer::m_userInfo->getRName(),m_imProtocol->getDataContent());
        }
    }
    else
    {//现在只能先通过已有好友得到name
        QString nickname;
        for(int i = 0; i < LogicLayer::m_friendInfoList->size(); i++)
        {
            if(LogicLayer::m_friendInfoList->at(i).getUID().toInt() == sendHost)
            {
                nickname = LogicLayer::m_friendInfoList->at(i).getRName();
            }
        }

        if(ModelCrowdInfoStatu::m_mapPriChatForm.contains(cidHost))
        {
            ModelCrowdInfoStatu::m_mapPriChatForm[cidHost]->slotCrowdChatWithAll(
                        nickname, m_imProtocol->getDataContent());
        }
        else
        {
            ModelCrowdInfoStatu::m_mapPriChatRecordNumber[cidHost]++;
            ModelCrowdInfoStatu::m_multiMapPriChatRecord.insert(sendHost, m_imProtocol->getDataContent());
        }
    }

}




void ExecUserCmd::execOperateCmdChatRecall(void)
{

}

///
/// \brief execOperateCmdMood
///
void ExecUserCmd::execOperateCmdMood(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_MOOD_ASK: execOperateCmdMoodAsk(); break;
    case OPE_CMD_MOOD_FRIEND: execOperateCmdMoodFriend(); break;
    case OPE_CMD_MOOD_ADD: execOperateCmdMoodAdd(); break;
    case OPE_CMD_MOOD_DEL: execOperateCmdMoodDel(); break;
    case OPE_CMD_MOOD_FAVOUR: execOperateCmdMoodFavour(); break;
    case OPE_CMD_MOOD_NOTIFY: execOperateCmdMoodNotify(); break;
    case OPE_CMD_MOOD_REVIEW: execOperateCmdMoodReview(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdMoodAsk(void)
{

}

void ExecUserCmd::execOperateCmdMoodFriend(void)
{

}

void ExecUserCmd::execOperateCmdMoodAdd(void)
{

}

void ExecUserCmd::execOperateCmdMoodDel(void)
{

}

void ExecUserCmd::execOperateCmdMoodFavour(void)
{

}

void ExecUserCmd::execOperateCmdMoodNotify(void)
{

}

void ExecUserCmd::execOperateCmdMoodReview(void)
{

}
