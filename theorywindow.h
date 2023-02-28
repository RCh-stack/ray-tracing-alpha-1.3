#ifndef THEORYWINDOW_H
#define THEORYWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTreeWidgetItem>

namespace Ui {
class TheoryWindow;
}

class TheoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TheoryWindow(QWidget *parent = 0);
    ~TheoryWindow();
    void set_window_options();
    void output_table_of_contents(int row_index);
    void open_file(QString path);

private slots:
    void on_button_prev_page_clicked();

    void on_button_next_page_clicked();

    void on_list_of_contents_itemClicked(QTreeWidgetItem *item);

private:
    Ui::TheoryWindow *ui;
    int pages_read;
};

#endif // THEORYWINDOW_H
