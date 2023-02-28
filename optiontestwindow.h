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
    void set_user(QString user);

private slots:
    void on_button_start_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

private:
    Ui::OptionTestWindow *ui;
};

#endif // OPTIONTESTWINDOW_H
