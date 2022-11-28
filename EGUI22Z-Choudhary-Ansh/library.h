#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDialog>

namespace Ui {
class Library;
}

class Library : public QDialog
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = nullptr);
    ~Library();

private:
    Ui::Library *ui;
};

#endif // LIBRARY_H
