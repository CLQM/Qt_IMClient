#include "formchatting.h"
#include "ui_formchatting.h"
#include "modelfriendinfostatu.h"

FormChatting::FormChatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChatting)
{
    ui->setupUi(this);
    m_friendInfo = new FriendInfo;

}

FormChatting::~FormChatting()
{
    delete ui;
}

void FormChatting::slotPrivateChatWithFriend(const QString sendhost, const QString content)
{
    QString line = tr("<b>%1</b> says: <i>%2</i>")
            .arg(sendhost).arg(content);
    ui->tb_recvMsg->append(line);
    ui->le_sendMsg->clear();
}

void FormChatting::updateFormFriendInfo(const FriendInfo &info)
{
    this->setWindowTitle(info.getRName());
    m_friendInfo->updataFriendInfo(&info);

    ui->le_uid->setText(m_friendInfo->getUID());
    ui->le_nickname->setText(m_friendInfo->getRName());
    ui->le_sign->setText(m_friendInfo->getSelfSign());
    ui->le_netyear->setText(m_friendInfo->getRTime());

    QList<QString> records =
                ModelFriendInfoStatu::m_multiMapPriChatRecord.values(m_friendInfo->getUID().toInt());
    for(int i = records.size() - 1; i > -1; i--)
    {
        slotPrivateChatWithFriend(m_friendInfo->getRName(), records[i]);
    }

    ModelFriendInfoStatu::m_mapPriChatRecordNumber[m_friendInfo->getUID().toInt()] = 0;
    ModelFriendInfoStatu::m_multiMapPriChatRecord.remove(m_friendInfo->getUID().toInt());
}

void FormChatting::on_tb_send_clicked()
{
    emit signalSendMessage(ui->le_uid->text(), ui->le_sendMsg->text());
}

void FormChatting::on_tb_cancle_clicked()
{
    ModelFriendInfoStatu::m_mapPriChatForm.remove(
                    m_friendInfo->getUID().toInt());
    this->close();
}
