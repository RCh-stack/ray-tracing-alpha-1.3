#ifndef OPTIONTESTWINDOW_H
#define OPTIONTESTWINDOW_H

#include <QDialog>
#include <QKeyEvent>

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
    void set_system_options();
    void set_list_tests();
    void set_visible_name_user();
    void delete_answers();
    void run_test();

    void set_id_user(QString user) { id_user = user; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

    bool check_test_passing(QString id_user, int id_theme);
    void set_allow_repeat_try(bool allow) { allow_repeat_try = allow; }
    bool get_allow_repeat_try() { return allow_repeat_try; }

private slots:
    void on_button_start_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

    void on_button_stats_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::OptionTestWindow *ui;
    QString id_user;
    QString fullname_user;
    bool allow_repeat_try;
};

#endif // OPTIONTESTWINDOW_H
