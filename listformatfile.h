#ifndef LISTFORMATFILE_H
#define LISTFORMATFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class ListFormatFile;
}

class ListFormatFile : public QDialog
{
    Q_OBJECT

public:
    explicit ListFormatFile(QWidget *parent = 0);
    ~ListFormatFile();

    void set_window_options();
    void output_data();
    void clear_table();

private slots:
    void on_button_add_clicked();

    void on_button_edit_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

public slots:
    void close_add_edit_window(int result);

private:
    Ui::ListFormatFile *ui;
};

#endif // LISTFORMATFILE_H
