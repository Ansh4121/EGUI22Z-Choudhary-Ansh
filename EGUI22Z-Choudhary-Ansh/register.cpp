#include "register.h"
#include "ui_register.h"

#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>

#include "user.h"
using json = nlohmann::json;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register() {
    delete ui;
}

void Register::on_pushButton_cancel_clicked() {
    hide();
}

void Register::on_pushButton_signUp_clicked() {
    std::string username = ui->lineEdit_username->text().toStdString();
    std::string email = ui->lineEdit_email->text().toStdString();
    std::string password = ui->lineEdit_password->text().toStdString();
    std::string confirmPassword = ui->lineEdit_confirmPassword->text().toStdString();

    bool isUsernameAlnum = std::all_of(username.begin(), username.end(), [](char const &c) {
        return std::isalnum(c);
    });
    bool isPasswordAlnum = std::all_of(username.begin(), username.end(), [](char const &c) {
        return std::isalnum(c);
    });

    // Form Validation
    if (password == "" || username == "") {
        QMessageBox::warning(this, "Empty String", "Fields cannot be left blank.");
        return;
    }

    if (password.length() < 3) {
        QMessageBox::warning(this, "Password too short", "Password length should atleast be 3 characters long.");
        return;
    }

    if (!isUsernameAlnum || !isPasswordAlnum) {
        QMessageBox::warning(this, "Only alphanumeric characters are allowed", "Username and Password aren't alphanumeric.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Password doess't match", "Password and Confirm Password fields doesn't match.");
        return;
    }

    QString usersFilePath = QDir::currentPath() + "/../../../../users.json";
    QFile userFile(usersFilePath);

    std::string usersJsonString;

    if (userFile.open(QIODevice::ReadOnly)) {
        usersJsonString = userFile.readAll().toStdString();
        userFile.close();
    } else {
        std::cout << "An unknow error has occurred" << std::endl;
    }

    json js = json::parse(usersJsonString);
    auto users = js.get<std::vector<User>>();

    // Check Existing User
    for (auto user: users) {
        if (username == user.user) {
            QMessageBox::warning(this, "Username should be unique", "User with the types username already exists.");
            return;
        }
    }

    users.push_back(User{ username, password});

    std::cout << json(users).dump() << std::endl;

    hide();

    if (userFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&userFile);
        stream << json(users).dump().c_str();
        userFile.close();
    } else {
        std::cout << "an error has occured" << std::endl;
    }
}
