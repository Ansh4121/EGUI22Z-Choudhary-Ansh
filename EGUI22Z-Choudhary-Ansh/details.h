#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
#include "book.h"

namespace Ui {
class Details;
}

class Details : public QDialog {
    Q_OBJECT

    public:
        explicit Details(QWidget *parent = nullptr);
        ~Details();
        void setBook(Book& book);

    private:
        Ui::Details *ui;
        Book book;
};

#endif // DETAILS_H
