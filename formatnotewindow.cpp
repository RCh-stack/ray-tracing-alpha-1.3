#include "formatnotewindow.h"
#include "ui_formatnotewindow.h"

FormatNoteWindow::FormatNoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatNoteWindow)
{
    ui->setupUi(this);

    set_window_options();
}

FormatNoteWindow::~FormatNoteWindow()
{
    delete ui;
}

//1.6
void FormatNoteWindow::set_window_options()
{
    QPixmap accept(":/icons/images/complete-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAccept(accept);
    QIcon ButtonCancel(cancel);
    QIcon ButtonInformation(help);

    ui->button_accept->setIcon(ButtonAccept);
    ui->button_cancel->setIcon(ButtonCancel);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void FormatNoteWindow::set_note_default()
{
    QFont font("Century Gothic", 10);
    ui->text_note->setFont(font);
    ui->text_note->setText(get_text_note());
}

// 1.6
void FormatNoteWindow::on_button_accept_clicked()
{
    set_text_note(ui->text_note->toPlainText().simplified());
    QMessageBox::information(this, "Уведомление", "Формат для вставки примечания установлен.");
    this->close();
}

// 1.6
void FormatNoteWindow::on_button_cancel_clicked()
{
    this->close();
}

void FormatNoteWindow::on_button_help_clicked()
{

}
