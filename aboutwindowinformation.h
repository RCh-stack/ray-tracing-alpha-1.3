#ifndef ABOUTWINDOWINFORMATION_H
#define ABOUTWINDOWINFORMATION_H

#include <QDialog>
#include <QUrl>
#include <QDesktopServices>

namespace Ui {
class AboutWindowInformation;
}

class AboutWindowInformation : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindowInformation(QWidget *parent = 0);
    ~AboutWindowInformation();

private slots:
    void on_button_close_clicked();

    void on_button_github_clicked();

    void on_button_telegram_clicked();

private:
    Ui::AboutWindowInformation *ui;
};

#endif // ABOUTWINDOWINFORMATION_H
