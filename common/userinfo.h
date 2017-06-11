#ifndef USERINFO_H
#define USERINFO_H
//=================用户信息=====================
#include <QString>
#include <QList>
#include "common.h"


class UserInfo :virtual public RegisterInfo ,virtual public IpAddrInfo,virtual public StatuInfo
{
public:
    UserInfo();
    UserInfo(const QString &uid, const QString &selfsign);
    ~UserInfo();

    void updataUserinfo(UserInfo *info);
    void updataUserinfo(const QString &uid,
                        const QString &selfsign);

    void clearUserinfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void);

    const QString &getUID(void) const;
    void setUID(const QString &uid);

    const QString &getSelfSign(void) const;
    void setSelfSign(const QString &selfsign);

private:
    QString m_UID;
    QString m_SelfSign;

};

typedef QList<UserInfo> List_UserInfo;

#endif // USERINFO_H
