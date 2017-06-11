#ifndef LOGIN_H
#define LOGIN_H
//============客户端的登录界面

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT


signals:
    void signalConnectServer(QString id, QString pswd);
    void signalRegister();

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void setIDPassword(QString id,QString pswd);

private slots:
    void on_pb_enter_clicked();

    void on_pb_register_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
