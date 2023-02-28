#ifndef ADDPRACTICWORK_H
#define ADDPRACTICWORK_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class AddPracticWork;
}

class AddPracticWork : public QDialog
{
    Q_OBJECT

public:
    explicit AddPracticWork(QWidget *parent = 0);
    ~AddPracticWork();

    void set_window_options();

private slots:
    void on_button_path_clicked();

    void on_button_help_clicked();

    void on_button_add_clicked();

    void on_button_exit_clicked();

private:
    Ui::AddPracticWork *ui;
};

#endif // ADDPRACTICWORK_H
