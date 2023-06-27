#ifndef USERHELPWINDOW_H
#define USERHELPWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class UserHelpWindow;
}

class UserHelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserHelpWindow(QWidget *parent = 0);
    ~UserHelpWindow();

    void set_window_options();
    void set_enabled_button(int id_page);
    int get_last_page();

    void open_file_by_code(int row_index);
    void open_file_by_name(QString name);
    void output_table_of_contents(QString path);

private slots:
    void on_button_prev_page_clicked();

    void on_button_next_page_clicked();

    void on_list_of_contents_itemClicked(QTreeWidgetItem *item);

private:
    Ui::UserHelpWindow *ui;
    int pages_read;
    QTreeWidgetItem *selected_item;
};

#endif // USERHELPWINDOW_H
