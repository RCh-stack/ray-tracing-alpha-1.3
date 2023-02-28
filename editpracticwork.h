#ifndef EDITPRACTICWORK_H
#define EDITPRACTICWORK_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class EditPracticWork;
}

class EditPracticWork : public QDialog
{
    Q_OBJECT

public:
    explicit EditPracticWork(QWidget *parent = 0);
    ~EditPracticWork();

    void set_window_options();

private slots:
    void on_button_path_clicked();

    void on_button_help_clicked();

    void on_button_edit_clicked();

    void on_button_exit_clicked();

private:
    Ui::EditPracticWork *ui;
};

#endif // EDITPRACTICWORK_H
