#ifndef USEROPTIONWINDOW_H
#define USEROPTIONWINDOW_H

#include <QDialog>

namespace Ui {
class UserOptionWindow;
}

class UserOptionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserOptionWindow(QWidget *parent = 0);
    ~UserOptionWindow();

private:
    Ui::UserOptionWindow *ui;
};

#endif // USEROPTIONWINDOW_H
