#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class Admin;
}

class Admin : public QDialog {
    Q_OBJECT

    public:
        explicit Admin(QWidget *parent = nullptr);
        ~Admin();
        void reloadBooks();
        void loadUsers();

    private slots:
        void on_pushButton_remove_clicked();
        void on_pushButton_logout_clicked();
        void on_comboBox_currentTextChanged(const QString &arg1);

        void on_listWidget_itemChanged(QListWidgetItem *item);

    private:
        Ui::Admin *ui;
};

#endif // ADMIN_H
