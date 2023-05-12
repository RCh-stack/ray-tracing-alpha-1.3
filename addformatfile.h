#ifndef ADDFORMATFILE_H
#define ADDFORMATFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AddFormatFile;
}

class AddFormatFile : public QDialog
{
    Q_OBJECT

public:
    explicit AddFormatFile(QWidget *parent = 0);
    ~AddFormatFile();

    void set_window_options();
    void add_new_format();

private slots:
    void on_button_save_clicked();

    void on_button_cancel_clicked();

    void on_AddFormatFile_finished(int result);

private:
    Ui::AddFormatFile *ui;
};

#endif // ADDFORMATFILE_H
