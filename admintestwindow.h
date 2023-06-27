#ifndef ADMINTESTWINDOW_H
#define ADMINTESTWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class AdminTestWindow;
}

class AdminTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminTestWindow(QWidget *parent = 0);
    ~AdminTestWindow();

    void set_window_options();

    void set_id_theme(int id) { id_theme = id; }
    int get_id_theme() { return id_theme; }

private slots:
    void on_action_help_triggered();

    void on_action_manual_triggered();

    void on_button_stats_clicked();

    void on_button_create_clicked();

    void on_button_edit_clicked();

    void on_button_help_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::AdminTestWindow *ui;
    int id_theme;
};

#endif // ADMINTESTWINDOW_H
