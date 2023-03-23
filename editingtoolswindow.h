#ifndef EDITINGTOOLSWINDOW_H
#define EDITINGTOOLSWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class EditingToolsWindow;
}

class EditingToolsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditingToolsWindow(QWidget *parent = 0);
    ~EditingToolsWindow();

    void set_window_options();
    void set_default_edit_options();
    void enabled_elements_in_form(bool enable);

    void set_name_font(QString name) { name_font = name; }
    QString get_name_font() { return name_font; }

    void set_size_font(int size) { size_font = size; }
    int get_size_font() { return size_font; }

    void set_id_font_color(int id) { id_font_color = id; }
    int get_id_font_color() { return id_font_color; }

private slots:
    void on_checkBox_clicked();

    void on_button_help_clicked();

    void on_button_save_clicked();

    void on_button_exit_clicked();

private:
    Ui::EditingToolsWindow *ui;
    QString name_font;
    int size_font;
    int id_font_color;
};

#endif // EDITINGTOOLSWINDOW_H
