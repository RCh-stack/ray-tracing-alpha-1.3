#ifndef USERPROFILEWINDOW_H
#define USERPROFILEWINDOW_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class UserProfileWindow;
}

class UserProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserProfileWindow(QWidget *parent = 0);
    ~UserProfileWindow();

    void set_window_options();

    void set_fullname(QString fullname);
    void set_role(QString role);
    void set_group(QString group);

private slots:
    void on_button_close_clicked();

    void on_button_help_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::UserProfileWindow *ui;
};

#endif // USERPROFILEWINDOW_H
