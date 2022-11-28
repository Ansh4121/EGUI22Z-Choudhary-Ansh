#include "dashboard.h"
#include "ui_dashboard.h"
#include "login.h"

#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <iostream>

#include "details.h"
#include "book.h"

Dashboard::Dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard() {
    delete ui;
}

void Dashboard::reloadBooks() {
    ui->listWidget->clear();
    for (auto& book: fetchBooks()) {
        if (book.user == user.user) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.title), ui->listWidget);
            item->setData(Qt::UserRole, book.id);
        }
    }
}

void Dashboard::reloadLibrary() {
    ui->listWidget_library->clear();
    for (auto& book: fetchBooks()) {
        if (book.user == "") {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.title), ui->listWidget_library);
            item->setData(Qt::UserRole, book.id);
        }
    }
}

void Dashboard::setUser(const User& val) {
    user = val;
    ui->label->setText("<h1>" + QString::fromStdString(val.user) + "</h1>");
    reloadBooks();
    reloadLibrary();
}

void Dashboard::on_pushButton_remove_clicked() {
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    int currentId = currentItem->data(Qt::UserRole).toInt();

    auto books = fetchBooks();

    for (auto& book: books) {
        if (currentId == book.id) {
            book.user = "";
        }
    }

    writeBooks(books);
    reloadBooks();
    reloadLibrary();
}

void Dashboard::on_pushButton_view_clicked() {
    Details* bookDetails = new Details(this);
    bookDetails->show();
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    int currentId = currentItem->data(Qt::UserRole).toInt();

    auto books = fetchBooks();

    for (auto& book: books) {
        if (currentId == book.id) {
            bookDetails->setBook(book);
        }
    }
}

void Dashboard::on_pushButton_borrow_clicked() {
    QListWidgetItem* currentItem = ui->listWidget_library->currentItem();
    int currentId = currentItem->data(Qt::UserRole).toInt();

    auto books = fetchBooks();

    for (auto& book: books) {
        if (currentId == book.id) {
            book.user = user.user;
        }
    }

    writeBooks(books);
    reloadBooks();
    reloadLibrary();
}

void Dashboard::on_comboBox_activated(int index) {
    if (index == 1) {
        ((Login*)(parent()))->deleteUser(user.user);
    }
    hide();
    Login* loginScreen = new Login();
    loginScreen->show();
}
