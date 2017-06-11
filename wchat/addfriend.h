#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

#include "common.h"

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT
signals:
    void signalFindFriend(QString uid);
    void signalAddFriendCancel();
    void signalAddFriend(QString uid);

private slots:
    void on_pb_search_clicked();

    void on_pb_add_clicked();

    void on_pb_cancle_clicked();


public:
    explicit AddFriend(QWidget *parent = 0);
    ~AddFriend();
    void updateSearchResult(UserInfo *info);

private:
    Ui::AddFriend *ui;
    UserInfo *m_info;
};

#endif // ADDFRIEND_H
