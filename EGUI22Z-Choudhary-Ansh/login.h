#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow {
    Q_OBJECT

    public:
        Login(QWidget *parent = nullptr);
        ~Login();
        void deleteUser(std::string username);

    private slots:
        void on_pushButton_register_clicked();

        void on_pushButton_login_clicked();

private:
        Ui::Login *ui;
};
#endif // LOGIN_H
