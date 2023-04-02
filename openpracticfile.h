#ifndef OPENPRACTICFILE_H
#define OPENPRACTICFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include "sql_requests.h"

namespace Ui {
class OpenPracticFile;
}

class OpenPracticFile : public QDialog
{
    Q_OBJECT

public:
    explicit OpenPracticFile(QWidget *parent = 0);
    ~OpenPracticFile();

    void set_window_options();
    void output_data();

    void set_id_work(int id) { id_work = id; }
    int get_id_work() { return id_work; }

private slots:
    void on_table_themes_cellDoubleClicked(int row, int column);

private:
    Ui::OpenPracticFile *ui;
    QSqlDatabase db;
    int id_work;
};

#endif // OPENPRACTICFILE_H
