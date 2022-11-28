#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog {
    Q_OBJECT

    public:
        explicit Dashboard(QWidget *parent = nullptr);
        ~Dashboard();
        void reloadBooks();
        void reloadLibrary();
        void setUser(const User& user);

    private slots:
        void on_pushButton_remove_clicked();
        void on_pushButton_view_clicked();
        void on_pushButton_borrow_clicked();
        void on_comboBox_activated(int index);

private:
        Ui::Dashboard *ui;
        User user;
};

#endif // DASHBOARD_H
