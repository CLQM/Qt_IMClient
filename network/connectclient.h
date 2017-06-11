#ifndef CONNECTCLIENT_H
#define CONNECTCLIENT_H

#include "improtocol.h"
#include "execusercmd.h"

#include <QObject>
#include <QUdpSocket>

class ExecUserCmd;

class ConnectClient : public QObject
{
    Q_OBJECT
signals:

public:
    explicit ConnectClient(QObject *parent = 0);
    ~ConnectClient();


public slots:
    void slotRecvMessage(void);
    void slotSendMessage(const QString &uid, const QString &msg);
    void slotSendCrowdMessage(const QString &cid,const QString &msg);

private:
    quint32 m_port;
    QUdpSocket *m_udpSocket;
    IMProtocol *m_protocol;
    ExecUserCmd *m_execUserCmd;
};

#endif // CONNECTCLIENT_H
