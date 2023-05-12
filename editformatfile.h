#ifndef EDITFORMATFILE_H
#define EDITFORMATFILE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class EditFormatFile;
}

class EditFormatFile : public QDialog
{
    Q_OBJECT

public:
    explicit EditFormatFile(QWidget *parent = 0);
    ~EditFormatFile();

    void set_window_options();
    void set_initial_data();
    void edit_selected_format();

    void set_id_format(int id) { id_format = id; }
    void set_name_format(QString name) { name_format = name; }
    void set_used_format(bool used) { used_format = used; }

    int get_id_format() { return id_format; }
    QString get_name_format() { return name_format; }
    bool get_used_format() { return used_format; }

private slots:
    void on_button_save_clicked();

    void on_button_cancel_clicked();

    void on_EditFormatFile_finished(int result);

private:
    Ui::EditFormatFile *ui;
    int id_format;
    QString name_format;
    bool used_format;
};

#endif // EDITFORMATFILE_H
