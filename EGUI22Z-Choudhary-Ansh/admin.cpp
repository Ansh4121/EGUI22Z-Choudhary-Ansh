#include "admin.h"
#include "ui_admin.h"

#include <QString>
#include "user.h"
#include "book.h"
#include "login.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    reloadBooks();
    loadUsers();
}

Admin::~Admin() {
    delete ui;
}

void Admin::reloadBooks() {
    ui->listWidget->clear();
    for (auto& book: fetchBooks()) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.title), ui->listWidget);
        item->setData(Qt::UserRole, book.id);
    }
}

void Admin::loadUsers() {
    for (auto& user: fetchUsers()) {
        ui->comboBox->addItem(QString::fromStdString(user.user));
    }
}

void Admin::on_pushButton_remove_clicked() {
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    int currentId = currentItem->data(Qt::UserRole).toInt();

    auto books = fetchBooks();
    int i = 1;

    for (auto& book: books) {
        if (currentId == book.id) {
            books.erase(books.begin() + i);
        }
        i++;
    }

    writeBooks(books);
    reloadBooks();
}

void Admin::on_pushButton_logout_clicked() {
    hide();
    Login* loginScreen = new Login();
    loginScreen->show();
}

void Admin::on_comboBox_currentTextChanged(const QString& qUsername){
    std::string username = qUsername.toStdString();

    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    int currentId = currentItem->data(Qt::UserRole).toInt();

    auto books = fetchBooks();

    for (auto& book: books) {
        if (currentId == book.id) {
            book.user = username;
        }
    }

    writeBooks(books);
}

void Admin::on_listWidget_itemChanged(QListWidgetItem *item) {
    std::string user = "No User";

    for (auto& book: fetchBooks()) {
        if (item->data(Qt::UserRole).toInt()) {
            user = book.user;
        }
    }

    ui->comboBox->setCurrentText(QString::fromStdString(user));
}
