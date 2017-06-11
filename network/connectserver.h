#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QObject>

#include "improtocol.h"
#include "execusercmd.h"

class QTcpSocket;
class ExecUserCmd;

class ConnectServer : public QObject
{
    Q_OBJECT

public slots:
    void readyToRead();

    void slotSendMsgToServer(QByteArray *buffer);
    void slotGetUserFriendList(UserInfo *info);

    void slotConnectServer(QString id, QString pswd);
    void slotRegisterAsk(QString name, QString pswd);

    void slotFindFriend(QString uid);
    void slotAddFriend(QString uid);

    const QString &getClientIpAddr(void) const;
    void setClientIpAddr(const QString &ipAddr);

    const QString &getClientPort(void) const;
    void setClientPort(const QString &port);

    void slotGetUserCrowdList(UserInfo *info);

public:
    explicit ConnectServer(QObject *parent = 0);
    ~ConnectServer();

private:
    QTcpSocket *m_tcpSocket;

    IMProtocol *m_protocol;
    ExecUserCmd *m_execUserCmd;

    QString m_serverIpAddr;
    QString m_serverPort;

    QString m_clientIpAddr;
    QString m_clientPort;
};

#endif // CONNECTSERVER_H
