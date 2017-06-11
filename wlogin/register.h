#ifndef REGISTER_H
#define REGISTER_H
//============注册界面

#include <QWidget>
#include <QString>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT
signals:
    void signalRegisterCancel(void);
    void signalRegisterAsk(QString name,QString pswd);

private slots:
    void on_pb_enter_clicked();

    void on_pb_cancel_clicked();

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
