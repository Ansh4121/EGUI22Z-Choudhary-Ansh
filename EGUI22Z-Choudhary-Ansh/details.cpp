#include "details.h"
#include "ui_details.h"
#include "book.h"

#include <QString>

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    ui->setupUi(this);
}

Details::~Details() {
    delete ui;
}

void Details::setBook(Book& val) {
    book = val;
    ui->label_title->setText("<h1>" + QString::fromStdString(val.title) + "</h1>");
    ui->label_date->setText(QString::fromStdString(std::to_string(val.date)));
    ui->label_author->setText(QString::fromStdString(val.author));
    ui->label_publisher->setText(QString::fromStdString(val.publisher));
}
