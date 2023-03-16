#ifndef OPTIONTESTWINDOW_H
#define OPTIONTESTWINDOW_H

#include <QDialog>

namespace Ui {
class OptionTestWindow;
}

class OptionTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionTestWindow(QWidget *parent = 0);
    ~OptionTestWindow();

    void set_window_options();
    void set_visible_name_user();

    void set_id_user(QString user) { id_user = user; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

private slots:
    void on_button_start_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

private:
    Ui::OptionTestWindow *ui;
    QString id_user;
    QString fullname_user;
};

#endif // OPTIONTESTWINDOW_H
