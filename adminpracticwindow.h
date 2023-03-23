#ifndef ADMINPRACTICWINDOW_H
#define ADMINPRACTICWINDOW_H

#include <QDialog>

namespace Ui {
class AdminPracticWindow;
}

class AdminPracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPracticWindow(QWidget *parent = 0);
    ~AdminPracticWindow();

    void set_window_options();

private:
    Ui::AdminPracticWindow *ui;
};

#endif // ADMINPRACTICWINDOW_H
