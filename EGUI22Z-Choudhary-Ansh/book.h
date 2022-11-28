#ifndef BOOK_H
#define BOOK_H

#include <json.hpp> // https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp
#include <iostream>

typedef struct {
    int id;
    std::string author;
    std::string title;
    std::string publisher;
    int date;
    std::string user;
    std::string reserved;
    std::string leased;
} Book;

void from_json(const nlohmann::json& j, Book& b);
void to_json(nlohmann::json& j, const Book& b);
std::vector<Book> fetchBooks();
void writeBooks(std::vector<Book>& books);

#endif // BOOK_H
