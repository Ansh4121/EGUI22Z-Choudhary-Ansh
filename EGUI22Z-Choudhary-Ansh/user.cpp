#include "user.h"

#include <QString>
#include <QDir>
#include "json.hpp"
using json = nlohmann::json;

void from_json(const nlohmann::json& j, User& p) {
    j.at("user").get_to(p.user);
    j.at("pwd").get_to(p.pwd);
}

void to_json(nlohmann::json& j, const User& p) {
    j = nlohmann::json{
      {"user", p.user}, {"pwd", p.pwd}
    };
}

std::vector<User> fetchUsers() {
    QString usersFilePath = QDir::currentPath() + "/../users.json";
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

    return users;
}

void writeUsers(std::vector<User>& users) {
    QString usersFilePath= QDir::currentPath() + "/../users.json";
    QFile usersFile(usersFilePath);

    if (usersFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&usersFile);
        stream << json(users).dump().c_str();
        usersFile.close();
    } else {
        std::cout << "an error has occured" << std::endl;
    }
}
