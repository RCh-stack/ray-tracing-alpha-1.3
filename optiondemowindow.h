#ifndef OPTIONDEMOWINDOW_H
#define OPTIONDEMOWINDOW_H

#include <QDialog>

namespace Ui {
class OptionDemoWindow;
}

class OptionDemoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDemoWindow(QWidget *parent = 0);
    ~OptionDemoWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::OptionDemoWindow *ui;
};

#endif // OPTIONDEMOWINDOW_H
