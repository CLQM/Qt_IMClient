#ifndef USERINFOFORM_H
#define USERINFOFORM_H

#include <QWidget>

#include "userinfo.h"

class UserInfo;

namespace Ui {
class UserInfoForm;
}

class UserInfoForm : public QWidget
{
    Q_OBJECT
signals:
    void signalSaveUserEdit(QString uid,QString name,QString sign);

public:
    explicit UserInfoForm(QWidget *parent = 0);
    ~UserInfoForm();
    static UserInfo *m_userInfo;

    void updateUserInfoToForm(UserInfo *info);
private slots:
    void on_pb_Edit_clicked();

    void on_pb_Save_clicked();

private:
    Ui::UserInfoForm *ui;


};

#endif // USERINFOFORM_H
