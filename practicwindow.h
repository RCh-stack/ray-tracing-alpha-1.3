#ifndef PRACTICWINDOW_H
#define PRACTICWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTreeWidgetItem>

namespace Ui {
class PracticWindow;
}

class PracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PracticWindow(QWidget *parent = 0);
    ~PracticWindow();

    void set_window_options();
    void output_table_of_contents(int row_index);
    void open_file(QString path);

private slots:
    void on_comboBox_works_currentIndexChanged(int index);

    void on_button_send_work_clicked();

    void on_button_edit_work_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::PracticWindow *ui;
};

#endif // PRACTICWINDOW_H
