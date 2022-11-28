#include "login.h"
#include "ui_login.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QCoreApplication>
#include <string>

#include "admin.h"
#include "dashboard.h"
#include "register.h"
#include "user.h"
#include "book.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login() {
    delete ui;
}

void Login::on_pushButton_register_clicked() {
    Register* registerDialog = new Register(this);
    registerDialog->show();

    // std::ifstream ifs("/json/users.json");
//    std::string t;
//    getline(ifs, t);
//    getline(ifs, t);
//    std::cout << t << std::endl;
//    json jf =  json::parse(ifs);
//    ifs.close();
/*
    auto users = jf.get<std::vector<User>>();
    std::cout << users[0].user << std::endl; // data read
    users[0].pwd = "secret";                 // data modification
    users.push_back(User{ "james", "567"});  // data insert
    users.erase(users.begin()+1);            // data removal

    std::ofstream ofs("output.json");
    ofs << std::setw(2) << nlohmann::json(users) << std::endl;
    ofs.close();
*/
}

void Login::on_pushButton_login_clicked() {
    std::string username = ui->lineEdit_username->text().toStdString();
    std::string password = ui->lineEdit_password->text().toStdString();

    for (auto user: fetchUsers()) {
        if (username == user.user && password == user.pwd) {
            if (user.user == "librarian") {
                hide();
                Admin* admin = new Admin(this);
                admin->show();
            } else {
                hide();
                Dashboard* dashboard = new Dashboard(this);
                dashboard->show();
                dashboard->setUser(user);
            }
            return;
       }
    }

    QMessageBox::critical(this, "User Athentication failed", "Username or Password is incorrect.");
}

void Login::deleteUser(std::string username) {
    auto users = fetchUsers();
    auto books = fetchBooks();

    int i = 1;
    for (auto& user: users) {
        if (user.user == username) {
            users.erase(users.begin() + i);
            i++;
        }
    }
    for (auto& book: books) {
        if (book.user == username) {
            book.user = "";
        }
    }
    writeBooks(books);
    writeUsers(users);
}
