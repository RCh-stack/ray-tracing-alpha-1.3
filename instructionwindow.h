#ifndef INSTRUCTIONWINDOW_H
#define INSTRUCTIONWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class InstructionWindow;
}

class InstructionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InstructionWindow(QWidget *parent = 0);
    ~InstructionWindow();

    void set_window_options();
    void open_file(int id_page);
    void output_table_of_contents(QString path);

private:
    Ui::InstructionWindow *ui;
    QSqlDatabase db;
};

#endif // INSTRUCTIONWINDOW_H
