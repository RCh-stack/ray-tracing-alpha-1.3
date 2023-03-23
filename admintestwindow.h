#ifndef ADMINTESTWINDOW_H
#define ADMINTESTWINDOW_H

#include <QDialog>

namespace Ui {
class AdminTestWindow;
}

class AdminTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminTestWindow(QWidget *parent = 0);
    ~AdminTestWindow();

    void set_window_options();

private:
    Ui::AdminTestWindow *ui;
};

#endif // ADMINTESTWINDOW_H
