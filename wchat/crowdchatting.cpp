#include "crowdchatting.h"
#include "ui_crowdchatting.h"
#include "modelcrowdinfostatu.h"

CrowdChatting::CrowdChatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrowdChatting)
{
    ui->setupUi(this);
    m_crowdInfo = new CrowdInfo;

}

CrowdChatting::~CrowdChatting()
{
    delete ui;
}

void CrowdChatting::slotCrowdChatWithAll(
const QString sendhost, const QString content)
{
//    QString line = tr("<b>%1</b> says: <i>%2</i>")
//            .arg(sendhost).arg(content);
//    ui->tb_recvMsg->append(line);
//    ui->le_sendMsg->clear();
    QString line  = tr("<b>%1</b> says: <i>%2</i>")
            .arg(sendhost).arg(content);
    ui->tb_recvMsg->append(line);
    ui->le_sendMsg->clear();
}

void CrowdChatting::updateFormCrowdInfo(const CrowdInfo &info)
{
    this->setWindowTitle(info.getCID());
    m_crowdInfo->updataCrowdInfo(&info);

    ui->le_cid->setText(m_crowdInfo->getCID());
    ui->le_crowdname->setText(m_crowdInfo->getCName());
    ui->le_intro->setText(m_crowdInfo->getCIntro());


//    QList<QString> records =
//                ModelCrowdInfoStatu::m_multiMapPriChatRecord.values(m_friendInfo->getUID().toInt());
//    for(int i = records.size() - 1; i > -1; i--)
//    {
//        slotPrivateChatWithFriend(m_friendInfo->getRName(), records[i]);
//    }

//    ModelCrowdInfoStatu::m_mapPriChatRecordNumber[m_friendInfo->getUID().toInt()] = 0;
//    ModelCrowdInfoStatu::m_multiMapPriChatRecord.remove(m_friendInfo->getUID().toInt());
}

void CrowdChatting::on_tb_send_clicked()
{
    emit signalSendMessage(ui->le_cid->text(), ui->le_sendMsg->text());
}

void CrowdChatting::on_tb_cancle_clicked()
{
//    ModelCrowdInfoStatu::m_mapPriChatForm.remove(
//                    m_friendInfo->getUID().toInt());
    this->close();
}
