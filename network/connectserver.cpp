#include "connectserver.h"

#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>

#include "logiclayer.h"

ConnectServer::ConnectServer(QObject *parent) :
    QObject(parent)
{
    m_serverIpAddr = "localhost";
    m_serverPort = "55555";

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol)
       {
           if(address.toString().contains("192.168"))
           {
               m_clientIpAddr = address.toString();
           }
       }
    }
    m_clientPort = "66666";

    m_execUserCmd = new ExecUserCmd;
    m_protocol = new IMProtocol;
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(disconnected()),
            m_tcpSocket, SLOT(deleteLater()));

    connect(m_tcpSocket, SIGNAL(readyRead()),
            this, SLOT(readyToRead()));

    connect(m_execUserCmd, SIGNAL(signalUserLoginSuccess(UserInfo*)),
            this, SLOT(slotGetUserFriendList(UserInfo*)));
    connect(m_execUserCmd, SIGNAL(signalUserLoginSuccess(UserInfo*)),
            (LogicLayer *)parent, SLOT(slotUserLoginSuccess(UserInfo*)));


    connect(m_execUserCmd, SIGNAL(signalUserRegisterSuccess(UserInfo*)),
            (LogicLayer *)parent, SLOT(slotUserRegisterSuccess(UserInfo*)));

    connect(m_execUserCmd, SIGNAL(signalUserFindFriendSuccess(UserInfo*)),
            (LogicLayer *)parent, SLOT(slotUserFindFriendSuccess(UserInfo*)));

    connect(m_execUserCmd, SIGNAL(signalUpdateFriendList()),
            (LogicLayer *)parent, SLOT(slotUpdateFriendList()));

    connect(m_execUserCmd, SIGNAL(signalUpdateCrowdList()),
            (LogicLayer *)parent, SLOT(slotUpdateCrowdList()));

    connect(m_execUserCmd, SIGNAL(signalSendMsgtoServer(QByteArray*)),
            this,SLOT(slotSendMsgToServer(QByteArray*)));

//    connect(m_execUserCmd, SIGNAL(signalUserLoginCrowdSuccess(UserInfo*)),
//            this,SLOT(slotGetUserCrowdList(UserInfo*)));  //不能用

    m_tcpSocket->connectToHost(m_serverIpAddr, m_serverPort.toInt());
}

ConnectServer::~ConnectServer()
{
    delete m_protocol;
    delete m_tcpSocket;
}

void ConnectServer::readyToRead()
{
    qDebug() << "void ConnectServer::readyToRead()";
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);
    m_protocol->unpackageMsg(in);
    m_execUserCmd->analysisProtocol(m_protocol);
//    m_tcpSocket->deleteLater();
}

void ConnectServer::slotGetUserCrowdList(UserInfo *info)
{//登录成功后的群列表请求
    QString msg = info->getUID();

    QByteArray *buffer =
            m_protocol->updataMsg(0,ERROR_INFO_NONE,
                                  USER_OPE_USER,OPE_CMD_USER_CROWD_ASK,
                                  MSG_USER_HOST_NONE,MSG_USER_HOST_NONE,
                                  msg.size(), msg);
    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotGetUserFriendList(UserInfo *info)
{//登录成功后的好友列表请求
    QString msg = info->getUID();

    QByteArray *buffer =
            m_protocol->updataMsg(0, ERROR_INFO_NONE,
                                  USER_OPE_USER, OPE_CMD_USER_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotSendMsgToServer(QByteArray *buffer)
{
    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotConnectServer(QString id, QString pswd)
{
//    m_tcpSocket->connectToHost(m_serverIpAddr, m_serverPort.toInt());
    QString msg = id + "|" + pswd + "|"
            + m_clientIpAddr + "|" + m_clientPort;
    QByteArray *buffer =
            m_protocol->updataMsg(LogicLayer::m_userInfo->getUID().toInt(),
                                  ERROR_INFO_NONE,
                                  USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotRegisterAsk(QString name, QString pswd)
{
//    m_tcpSocket->connectToHost(m_serverIpAddr, m_serverPort.toInt());
    QString msg = name + "|" + pswd + "|"
            + m_clientIpAddr + "|" + m_clientPort;
    QByteArray *buffer =
            m_protocol->updataMsg(0, ERROR_INFO_NONE,
                                  USER_OPE_LOGIN, OPE_CMD_REGISTER_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotFindFriend(QString uid)
{
    QString msg = uid;
    QByteArray *buffer =
            m_protocol->updataMsg(0, ERROR_INFO_NONE,
                                  USER_OPE_FRIEND, OPE_CMD_FRIEND_FIND,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    m_tcpSocket->write(*buffer);
}

void ConnectServer::slotAddFriend(QString uid)
{//2
    QString msg = uid + "|" + LogicLayer::m_userInfo->getUID();
    QByteArray *buffer =
            m_protocol->updataMsg(LogicLayer::m_userInfo->getUID().toInt(), ERROR_INFO_NONE,
                                  USER_OPE_FRIEND, OPE_CMD_FRIEND_ASK,
                                  MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                  msg.size(), msg);

    m_tcpSocket->write(*buffer);
}

const QString &ConnectServer::getClientIpAddr(void) const
{
    return m_clientIpAddr;
}
void ConnectServer::setClientIpAddr(const QString &ipAddr)
{
    m_clientIpAddr = ipAddr;
}

const QString &ConnectServer::getClientPort(void) const
{
    return m_clientPort;
}
void ConnectServer::setClientPort(const QString &port)
{
    m_clientPort = port;
}

