#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TestWindow;
}

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

    void set_window_options();
    void reset_answers();

private slots:
    void on_button_prev_question_clicked();

    void on_button_next_question_clicked();

    void on_button_complete_test_clicked();

    void on_button_help_clicked();

private:
    Ui::TestWindow *ui;
    int num_question;
};

#endif // TESTWINDOW_H
