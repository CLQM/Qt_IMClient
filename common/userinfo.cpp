#include "userinfo.h"
#include <QDebug>

UserInfo::UserInfo()
{
}

UserInfo::UserInfo(const QString &uid,
                   const QString &selfsign)
{
    updataUserinfo(uid,selfsign);
}

UserInfo::~UserInfo()
{}

void UserInfo::updataUserinfo(UserInfo *info)
{
    updataIpAddrinfo(info->getIpID(),info->getIpAddr(),info->getPort());
    updataRegisterinfo(info->getRID(),info->getRName(), info->getRPassword(),
                       info->getRTime());//userinfofrom不能更新name的解决方法
    m_UID = info->getUID();
    m_SelfSign = info->getSelfSign();
}

void UserInfo::updataUserinfo(const QString &uid,
                              const QString &selfsign)
{
    m_UID = uid;
    m_SelfSign =selfsign;
}
void UserInfo::printInfos(void) const
{
    qDebug() << "=======UserInfo=========";
    qDebug() << "ID" << getUID();
    qDebug() << "Self Sign" << getSelfSign();
    qDebug() << "=======UserInfo========";
}

QString *UserInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getUID());
    data->append("|");
    data->append(getSelfSign());

    return data;
}

void UserInfo::setUID(const QString &uid)
{
    m_UID = uid;
}

const QString &UserInfo::getUID(void) const
{
    return m_UID;
}

void UserInfo::setSelfSign(const QString &selfsign)
{
    m_SelfSign = selfsign;
}

const QString &UserInfo::getSelfSign(void) const
{
    return m_SelfSign;
}

