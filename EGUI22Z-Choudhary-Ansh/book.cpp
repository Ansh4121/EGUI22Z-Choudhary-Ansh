#include "book.h"

#include <QString>
#include <QDir>
#include "json.hpp"
using json = nlohmann::json;

void from_json(const nlohmann::json& j, Book& b) {
    j.at("id").get_to(b.id);
    j.at("author").get_to(b.author);
    j.at("title").get_to(b.title);
    j.at("publisher").get_to(b.publisher);
    j.at("date").get_to(b.date);
    j.at("user").get_to(b.user);
    j.at("reserved").get_to(b.reserved);
    j.at("leased").get_to(b.leased);
}

void to_json(nlohmann::json& j, const Book& b) {
    j = nlohmann::json{
        {"id", b.id},
        {"author", b.author},
        {"title", b.title},
        {"publisher", b.publisher},
        {"date", b.date},
        {"user", b.user},
        {"reserved", b.reserved},
        {"leased", b.leased}
    };
}

std::vector<Book> fetchBooks() {
    QString booksFilePath= QDir::currentPath() + "/../books.json";
    QFile booksFile(booksFilePath);

    std::string booksJsonString;

    if (booksFile.open(QIODevice::ReadOnly)) {
        booksJsonString = booksFile.readAll().toStdString();
        booksFile.close();
    } else {
        std::cout << "An unknow error has occurred" << std::endl;
    }

    json js = json::parse(booksJsonString);
    auto books = js.get<std::vector<Book>>();

    return books;
}

void writeBooks(std::vector<Book>& books) {
    QString booksFilePath= QDir::currentPath() + "/../books.json";
    QFile booksFile(booksFilePath);

    if (booksFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&booksFile);
        stream << json(books).dump().c_str();
        booksFile.close();
    } else {
        std::cout << "an error has occured" << std::endl;
    }
}
