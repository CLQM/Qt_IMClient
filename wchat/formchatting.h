#ifndef FORMCHATTING_H
#define FORMCHATTING_H

#include <QWidget>
#include <QString>

#include "friendinfo.h"

namespace Ui {
class FormChatting;
}

class FormChatting : public QWidget
{
    Q_OBJECT
signals:
    void signalSendMessage(const QString &uid, const QString &msg);
public:
    explicit FormChatting(QWidget *parent = 0);
    ~FormChatting();

    void slotPrivateChatWithFriend(
    const QString sendhost, const QString content);
    void updateFormFriendInfo(const FriendInfo &info);

private slots:
    void on_tb_send_clicked();

    void on_tb_cancle_clicked();

private:
    Ui::FormChatting *ui;
    FriendInfo *m_friendInfo;
};

#endif // FORMCHATTING_H
