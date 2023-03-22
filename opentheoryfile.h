#ifndef OPENTHEORYFILE_H
#define OPENTHEORYFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include "sql_requests.h"

namespace Ui {
class OpenTheoryFile;
}

class OpenTheoryFile : public QDialog
{
    Q_OBJECT

public:
    explicit OpenTheoryFile(QWidget *parent = 0);
    ~OpenTheoryFile();

    void set_window_options();
    void output_data();

    void set_id_page(int id) { id_page = id; }
    int get_id_page() { return id_page; }

private slots:
    void on_table_themes_cellDoubleClicked(int row, int column);

private:
    Ui::OpenTheoryFile *ui;
    QSqlDatabase db;
    int id_page;
};

#endif // OPENTHEORYFILE_H
