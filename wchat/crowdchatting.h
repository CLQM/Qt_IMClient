#ifndef CROWDCHATTING_H
#define CROWDCHATTING_H

#include <QWidget>
#include <QString>

#include "crowdinfo.h"

namespace Ui {
class CrowdChatting;
}

class CrowdChatting : public QWidget
{
    Q_OBJECT
signals:
    void signalSendMessage(const QString &uid, const QString &msg);
public:
    explicit  CrowdChatting(QWidget *parent = 0);
    ~CrowdChatting();

    void slotCrowdChatWithAll(const QString sendhost, const QString content);
    void updateFormCrowdInfo(const CrowdInfo &info);

private slots:
    void on_tb_send_clicked();

    void on_tb_cancle_clicked();

private:
    Ui::CrowdChatting *ui;
    CrowdInfo *m_crowdInfo;
};

#endif // CROWDCHATTING_H
