#include "library.h"
#include "ui_library.h"
#include <QFile>
#include <QDir>
#include <iostream>
#include "book.h"
using json = nlohmann::json;

Library::Library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    QString booksFilePath= QDir::currentPath() + "/../../../../books.json";
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

Library::~Library() {
    delete ui;
}
