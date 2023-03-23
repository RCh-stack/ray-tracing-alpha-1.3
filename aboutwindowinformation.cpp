#include "aboutwindowinformation.h"
#include "ui_aboutwindowinformation.h"

AboutWindowInformation::AboutWindowInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindowInformation)
{
    ui->setupUi(this);

    set_window_options();
}

AboutWindowInformation::~AboutWindowInformation()
{
    delete ui;
}

// 1.4
void AboutWindowInformation::set_window_options()
{
    QPixmap github(":/icons/images/github-button.png");
    QPixmap telegram(":/icons/images/telegram-button.png");

    QIcon ButtonGithub(github);
    QIcon ButtonTelegram(telegram);

    ui->button_github->setIcon(ButtonGithub);
    ui->button_telegram->setIcon(ButtonTelegram);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(":/icons/images/main_icon.ico"));
    ui->graphicsView->setScene(scene);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AboutWindowInformation::on_button_close_clicked()
{
    this->close();
}

void AboutWindowInformation::on_button_github_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/RCh-stack/ray-tracing-alpha-1.5"));
}

void AboutWindowInformation::on_button_telegram_clicked()
{
    QDesktopServices::openUrl(QUrl("http://t.me/roch2002"));
}
