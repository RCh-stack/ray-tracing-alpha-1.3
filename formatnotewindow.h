#ifndef FORMATNOTEWINDOW_H
#define FORMATNOTEWINDOW_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class FormatNoteWindow;
}

class FormatNoteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FormatNoteWindow(QWidget *parent = 0);
    ~FormatNoteWindow();

    void set_window_options();
    void set_note_default();

    void set_text_note(QString text) { text_note = text; }
    QString get_text_note() { return text_note; }

private slots:
    void on_button_accept_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

private:
    Ui::FormatNoteWindow *ui;
    QString text_note;
};

#endif // FORMATNOTEWINDOW_H
