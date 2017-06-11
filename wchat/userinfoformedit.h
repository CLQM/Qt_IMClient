#ifndef USERINFOFORMEDIT_H
#define USERINFOFORMEDIT_H

#include <QWidget>

namespace Ui {
class UserInfoFormEdit;
}

class UserInfoFormEdit : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfoFormEdit(QWidget *parent = 0);
    ~UserInfoFormEdit();

public slots:
    void slotUserEditAsk();

private:
    Ui::UserInfoFormEdit *ui;
};

#endif // USERINFOFORMEDIT_H
