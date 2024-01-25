#ifndef RECOVERPASSWORD_H
#define RECOVERPASSWORD_H

#include <QMainWindow>

namespace Ui {
class RecoverPassword;
}

class RecoverPassword : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecoverPassword(QWidget *parent = nullptr);
    ~RecoverPassword();

private slots:
    void changePassword(); // Added slot for changing password

private:
    Ui::RecoverPassword *ui;
};

#endif // RECOVERPASSWORD_H
