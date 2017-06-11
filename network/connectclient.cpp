#include "connectclient.h"
#include "formchatting.h"

#include <QDebug>


ConnectClient::ConnectClient(QObject *parent) : QObject(parent)
{
    m_port = 66666;
    m_udpSocket = new QUdpSocket();

    m_protocol = new IMProtocol();
    m_execUserCmd =new ExecUserCmd();
#ifdef Q_OS_LINUX
     m_udpSocket->bind(m_port, QUdpSocket::ShareAddress);
#else //Q_OS_WIN32
     m_udpSocket->bind(m_port, QUdpSocket::ReuseAddressHint);//即使已经绑定了也可以申请
#endif
    connect(m_udpSocket, SIGNAL(readyRead()),
            this, SLOT(slotRecvMessage())); //  如果不读已接受数据将不再产生readyRead()信号
}

ConnectClient::~ConnectClient()
{
    delete m_udpSocket;
    delete m_protocol;
    delete m_execUserCmd;
}

void ConnectClient::slotRecvMessage()
{
    while(m_udpSocket->hasPendingDatagrams())//当有数据包需要读时为真
    {
        QByteArray buffer;
        buffer.resize(m_udpSocket->pendingDatagramSize());//获得第一个数据包的长度
        /*将合格的数据包储存到data中*/
        m_udpSocket->readDatagram(buffer.data(), buffer.size());

        QDataStream in(buffer);//用buffer制作字节流
        m_protocol->unpackageMsg(in);//字节流按已定协议分块
        m_execUserCmd->analysisProtocol(m_protocol);//分析数据
    }
}

void ConnectClient::slotSendMessage(
        const QString &uid, const QString &msg)
{//私聊发送
    QByteArray *buffer =
            m_protocol->updataMsg(
                0,ERROR_INFO_NONE,USER_OPE_CHAT,
                OPE_CMD_CHAT_PRIVATE,uid.toInt(),LogicLayer::m_userInfo->getUID().toInt(),
                msg.size(),msg);
    m_udpSocket->writeDatagram(*buffer,QHostAddress::Broadcast,m_port);
}


void ConnectClient::slotSendCrowdMessage(
        const QString &cid, const QString &msg)
{//群聊发送
    QByteArray *buffer =
            m_protocol->updataMsg(
                0,ERROR_INFO_NONE,USER_OPE_CHAT,
                OPE_CMD_CHAT_CROWD,cid.toInt(),LogicLayer::m_userInfo->getUID().toInt(),
                msg.size(),msg);
    qDebug() << msg;
    m_udpSocket->writeDatagram(*buffer,QHostAddress::Broadcast,m_port);
}
